#ifndef TINDICATOR_H
#define TINDICATOR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSize>
#include <QLayout>
#include <QSpinBox>
#include <QToolButton>
#include <QDebug>
#include <QKeyEvent>
#include <iostream>

using namespace std;

class TDigitIndicator : public QPushButton
{
    Q_OBJECT
public:
    TDigitIndicator(QSize _size,QWidget *parent = 0):QPushButton(parent)
    {
        setCheckable(true);
        setEnabled(true);
        setMaximumSize(_size);
        setMinimumSize(_size);
    }
    void setIOValue(int _io_value){setChecked(_io_value);}
    int getIOValue(){return isChecked();}
};
class TAnalogIndicator : public QSpinBox
{
    Q_OBJECT
public:
    TAnalogIndicator(QWidget *parent = 0):QSpinBox(parent)
    {
        setReadOnly(true);
        setMinimum(0);
        setMaximum(327680);
        setButtonSymbols(QSpinBox::ButtonSymbols::NoButtons);
    }
    void setIOValue(int _io_value)
    {
        if(!isEditing)
            setValue(_io_value);
    }
    int getIOValue()
    {
        int v=value();
        isEditing=false;
        return v;
    }
    bool isEditing{false};
protected:
    void keyPressEvent(QKeyEvent * event)
    {
        isEditing=true;
        QSpinBox::keyPressEvent(event);
    }
};

class TButton : public TDigitIndicator
{
    Q_OBJECT
public:
    TButton(QSize _size,QWidget *parent = 0):TDigitIndicator(_size,parent){}
};

class TSwitch : public TDigitIndicator
{
    Q_OBJECT
public:
    TSwitch(QSize _size,QWidget *parent = 0):TDigitIndicator(_size,parent){}
};

class TLed : public TDigitIndicator
{
    Q_OBJECT
public:
    TLed(QSize _size,QWidget *parent = 0):TDigitIndicator(_size,parent){setEnabled(false);}
};


class TLabel : public TAnalogIndicator
{
    Q_OBJECT
public:
    TLabel(QWidget *parent = 0):TAnalogIndicator(parent){}
};

class TSpin : public TAnalogIndicator
{
    Q_OBJECT
public:
    TSpin(QWidget *parent = 0):TAnalogIndicator(parent){setReadOnly(false);}
};

class TCaption : public QLineEdit
{
    Q_OBJECT
public:
    TCaption(const QString& _str,QWidget *parent = 0):QLineEdit(_str,parent){setReadOnly(true);}

protected:
    void mouseDoubleClickEvent(QMouseEvent *)
    {
        setReadOnly(false);
    }
    void keyPressEvent(QKeyEvent * event)
    {
        if(event->key()==Qt::Key_Return)
            setReadOnly(true);
        QLineEdit::keyPressEvent(event);
    }
};


class TIndicator : public QFrame
{
    Q_OBJECT

public:
    enum class Orientation:int{LeftToRight,RightToLeft,UpToDown,DownToUp};
    enum class IndType{Label,Spin,Led,Button,Switch};
    explicit TIndicator(const IndType _type = IndType::Button,const QString& _pre_caption = "",const QString& _post_caption = "",Orientation _orientation = Orientation::LeftToRight,QSize _size = QSize(32,32),int _value=0,QVector<int> _src_id=QVector<int>(),QWidget *parent = 0);
    QWidget* genInd();
    void setValue(int _value);
    int getValue();
    void setPreCaption(const QString& _str);
    void setPostCaption(const QString& _str);
    void setOrientation(const Orientation _orientation);
    void setSize(const QSize _size);
    QVector<int> getSrcId();
    friend ostream& operator<<(ostream &_os, const TIndicator &_ind)
    {
        //_os<<_ind.preCaption->text().toStdString()<<"\n";
        _os<<_ind.postCaption->text().toStdString()<<"\n";
        return _os;
    }

signals:
    void signalValueChanged(QVector<int>,int);
public slots:
    void slotValueChanged();
private:
    IndType type;
    Orientation orientation;
    QSize size;    
    QVector<QWidget*> widgets;
    QLabel* preCaption;
    TCaption* postCaption;
    QWidget* ind;
    QLayout* layout{nullptr};
    QVector<int> srcId;
    int value{0};
    void build();
};

#endif // TINDICATOR_H
