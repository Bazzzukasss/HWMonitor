#ifndef NETMONITOR_H
#define NETMONITOR_H

#include <QWidget>
#include "NetUDPClient_Linpack.h"
#include "tpanel.h"
#include "tindicator.h"
#include <iostream>
#include <fstream>
using namespace std;

class NetMonitor : public QWidget
{
    Q_OBJECT
public:
    explicit NetMonitor(HWSession _session,NetUDPClient_Linpack* _client,QWidget *parent = 0,int _line_count=4,int _sub_line_count=4,bool _is_emulation_mode=false);
    void reconnect(QString _ip,int _port);
    void reconnect(HWSession _session);
    void setLineCount(int _line_count,int _sub_line_count);
    void setTitle(const QString& _title);
    friend ostream& operator<<(ostream& _os,const NetMonitor& _monitor)
    {
        for(auto p:_monitor.panels)
            _os<<*p;
        return _os;
    }
    void build();


signals:

public slots:
    void slotApply(QVector<int> _src_id,int _value);
    void slotRefresh();
private:
    HWSession session;
    QWidget* parentWidget{nullptr};
    int lineCount{1};
    int subLineCount{1};
    bool isEmulationMode{false};

    NetUDPClient_Linpack* client{nullptr};
    QString title;
    QHBoxLayout* layout{nullptr};
    TPanel* dashBoard{nullptr};
    QVector<TPanel*> panels;
    vector<string> captions;
    vector<string>::iterator captions_it;
    void saveCaptions();
    void loadCaptions();
    string getCaptionsFileName();
    string getNextCaption();

};

#endif // NETMONITOR_H
