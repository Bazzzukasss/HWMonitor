#include "NetMonitor.h"
#include <QDebug>
#include <QApplication>
NetMonitor::NetMonitor(HWSession _session,NetUDPClient_Linpack* _client,QWidget *parent,int _line_count,int _sub_line_count,bool _is_emulation_mode):
    QWidget(parent),session(_session),parentWidget(parent),lineCount(_line_count),subLineCount(_sub_line_count),isEmulationMode(_is_emulation_mode)
{
    client=_client;
    client->reconnect();
    client->send_CMD_GET(isEmulationMode);
    client->getNetDevice()->genPCModules();
    title=session.getNameHostPort();
    build();
}

void NetMonitor::slotRefresh()
{
    const NetModule* pModule;
    TPanel* pPanel;
    int mCount(client->getNetDevice()->getLPModulesCount());
    client->send_CMD_SET(isEmulationMode);
    for(int m=0;m<mCount;m++)
    {
        pModule=client->getNetDevice()->getLPModule(m);
        pPanel=panels[m];
        int i=0;
        for(auto ind:pPanel->getElements())
            dynamic_cast<TIndicator*>(ind)->setValue(pModule->getIOValue(i++));
    }
}

string NetMonitor::getCaptionsFileName()
{
    return (QString(QApplication::applicationDirPath()+"/"+session.getNameHostPort()).toStdString());
}

string NetMonitor::getNextCaption()
{
    if(captions.empty())
        return "";
    if(captions_it!=captions.end())
    {
        string caption;
        caption=*captions_it++;
        return caption;
    }
    else
        return "";
}

void NetMonitor::saveCaptions()
{

    ofstream f(getCaptionsFileName());
    copy(
                panels.begin(),
                panels.end(),
                ostream_iterator<TPanel*>(f,"\n")
                );

}
void NetMonitor::loadCaptions()
{
    ifstream f(getCaptionsFileName());
    captions.clear();
    copy(
                istream_iterator<string>(f),
                istream_iterator<string>(),
                back_inserter(captions)
                );
    captions_it=captions.begin();
}
void NetMonitor::slotApply(QVector<int> _src_id,int _value)
{
    int m(_src_id[0]),i(_src_id[1]);
    qDebug()<<"Apply:"<<m<<i<<_value;
    client->getNetDevice()->setPCModuleValue(m,i,_value);
    client->getNetDevice()->addSendModuleId(m);
}

void NetMonitor::reconnect(QString _ip, int _port)
{
    client->reconnect(_ip,_port);
    client->send_CMD_GET(isEmulationMode);
    client->getNetDevice()->genPCModules();
    build();
}

void NetMonitor::reconnect(HWSession _session)
{
    saveCaptions();
    session=_session;
    title=session.getNameHostPort();
    reconnect(session.getHost(),session.getPort().toInt());
}

void NetMonitor::setLineCount(int _line_count,int _sub_line_count)
{
    lineCount=_line_count;
    subLineCount=_sub_line_count;
    build();
}

void NetMonitor::setTitle(const QString& _title)
{
    title = _title;
    if(dashBoard!=nullptr)
        dashBoard->setTitle(title);
}


void NetMonitor::build()
{
    if(parentWidget)
    {
        TIndicator* pIndicator;
        string pre_caption="",post_caption="";
        string mode_str[]={"in/out","in","out"};
        QVector<int> src_id(2);

        int io_mode;
        if(dashBoard!=nullptr)
            delete dashBoard;
        if(layout!=nullptr)
            delete layout;
        panels.clear();

        loadCaptions();

        dashBoard = new TPanel(this);

        layout= new QHBoxLayout(parentWidget);
        layout->setSpacing(0);
        layout->setMargin(0);

        TPanel* subPanel;
        const NetModule* pModule;
        TIndicator::IndType indType;

        int mCount(client->getNetDevice()->getLPModulesCount());
        dashBoard->setLineCount(lineCount);
        dashBoard->setTitle(title);
        for(int m=0;m<mCount;m++)
        {
            getNextCaption();
            pModule=client->getNetDevice()->getLPModule(m);
            subPanel=dynamic_cast<TPanel*>(dashBoard->addElement(new TPanel()));
            subPanel->setLineCount(subLineCount);
            io_mode=pModule->getMode();
            subPanel->setTitle(QString().fromStdString("Module:"+pModule->getName()+"("+mode_str[io_mode]+")"));
            switch(io_mode)
            {
                case MDL_MODE_IN:
                    if(pModule->getType()==MDL_TYPE_DIGITAL)
                        indType=TIndicator::IndType::Led;
                    else
                        indType=TIndicator::IndType::Label;
                break;
                case MDL_MODE_OUT:
                    if(pModule->getType()==MDL_TYPE_DIGITAL)
                        indType=TIndicator::IndType::Switch;
                    else
                        indType=TIndicator::IndType::Spin;
                break;
                default:
                case MDL_MODE_INOUT:
                    if(pModule->getType()==MDL_TYPE_DIGITAL)
                        indType=TIndicator::IndType::Button;
                    else
                        indType=TIndicator::IndType::Spin;
                break;
            }

            src_id[0]=m;
            for(int i=0;i<pModule->getIOValuesCount();i++)
            {
                if(captions.empty())
                    post_caption="port"+QString().number(i).toStdString();
                else
                    post_caption=getNextCaption();
                src_id[1]=i;
                pIndicator=dynamic_cast<TIndicator*>(subPanel->addElement(new TIndicator(indType,QString().fromStdString(pre_caption),QString().fromStdString(post_caption),TIndicator::Orientation::LeftToRight,QSize(24,24),pModule->getIOValue(i),src_id)));
                connect(pIndicator,SIGNAL(signalValueChanged(QVector<int>,int)),this,SLOT(slotApply(QVector<int>,int)));
            }

            panels.push_back(subPanel);
        }

        layout->addWidget(dashBoard);
    }
}
