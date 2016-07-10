#include "tindicator.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
TIndicator::TIndicator(const IndType _type,const QString& _pre_caption,const QString& _post_caption,Orientation _orientation,QSize _size,int _value,QVector<int> _src_id,QWidget *parent) :
    QFrame(parent),type(_type),orientation(_orientation),size(_size),srcId(_src_id)
{
    QFont font(this->font());
    font.setBold(true);
    preCaption = new QLabel(_pre_caption,this);
    postCaption = new TCaption(_post_caption,this);
    ind = genInd();

    if((_type==IndType::Button)||(_type==IndType::Switch)||(_type==IndType::Led))
    {
        widgets.push_back(preCaption);
        widgets.push_back(ind);
        widgets.push_back(postCaption);
    }
    else
    {
        widgets.push_back(preCaption);
        widgets.push_back(postCaption);
        widgets.push_back(ind);
    }


    ind->setFont(font);
    ind->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    setValue(_value);
    build();
}

QWidget *TIndicator::genInd()
{
    if(type==IndType::Led)
    {
        TLed* pLed =new TLed(size,this);
        return pLed;
    }
    if(type==IndType::Button)
    {
        TButton* pButton =new TButton(size,this);
        connect(pButton,SIGNAL(clicked()),this,SLOT(slotValueChanged()));
        return pButton;
    }
    if(type==IndType::Switch)
    {
        TSwitch* pSwitch =new TSwitch(size,this);
        connect(pSwitch,SIGNAL(clicked()),this,SLOT(slotValueChanged()));
        return pSwitch;
    }
    if(type==IndType::Label)
    {
        TLabel* pLabel =new TLabel(this);
        return pLabel;
    }
    if(type==IndType::Spin)
    {
        TSpin* pSpin =new TSpin(this);
        connect(pSpin,SIGNAL(editingFinished()),this,SLOT(slotValueChanged()));
        return pSpin;
    }
    return nullptr;
}
void TIndicator::build()
{
    if(layout!=nullptr)
        delete layout;

    if(orientation==Orientation::LeftToRight)
    {
        preCaption->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        postCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        layout= new QHBoxLayout(this);
        for(auto w:widgets)
            layout->addWidget(w);
    }
    if(orientation==Orientation::RightToLeft)
    {
        preCaption->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
        postCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        layout= new QHBoxLayout(this);
    }
    if(orientation==Orientation::UpToDown)
    {
        preCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        postCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        layout= new QVBoxLayout(this);
    }
    if(orientation==Orientation::DownToUp)
    {
        preCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        postCaption->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        layout= new QVBoxLayout(this);
    }
    layout->setSpacing(2);
    layout->setMargin(0);
    for(auto w:widgets)
        layout->addWidget(w);
}

void TIndicator::setValue(int _value)
{
    TDigitIndicator* pIndD=dynamic_cast<TDigitIndicator*>(ind);
    TAnalogIndicator* pIndA=dynamic_cast<TAnalogIndicator*>(ind);
    if(pIndD)pIndD->setIOValue(_value);
    if(pIndA)pIndA->setIOValue(_value);
}

int TIndicator::getValue()
{
    return value;
}

void TIndicator::setPreCaption(const QString &_str)
{
    preCaption->setText(_str);
}

void TIndicator::setPostCaption(const QString &_str)
{
    postCaption->setText(_str);
}

void TIndicator::setOrientation(const TIndicator::Orientation _orientation)
{
    orientation=_orientation;
    build();
}

void TIndicator::setSize(const QSize _size)
{
    size=_size;
    build();
}

QVector<int> TIndicator::getSrcId()
{
    return srcId;
}

void TIndicator::slotValueChanged()
{
    TDigitIndicator* pIndD=dynamic_cast<TDigitIndicator*>(ind);
    TAnalogIndicator* pIndA=dynamic_cast<TAnalogIndicator*>(ind);
    if(pIndD)value=pIndD->getIOValue();
    if(pIndA)value=pIndA->getIOValue();
    emit signalValueChanged(srcId,value);
}
