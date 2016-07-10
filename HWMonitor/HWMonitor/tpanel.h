#ifndef TPANEL_H
#define TPANEL_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QFrame>
#include <QGroupBox>
#include <iostream>
#include "tindicator.h"
using namespace std;
class TPanel : public QGroupBox
{
    Q_OBJECT
public:
    explicit TPanel(QWidget *parent = 0);
    ~TPanel();
    QWidget* addElement(QWidget* _element);
    void setLineCount(int _line_count);
    QVector<QWidget*>& getElements();
    friend ostream& operator<<(ostream& _os,const TPanel* _panel)
    {
        _os<<*_panel;
        return _os;
    }
    friend ostream& operator<<(ostream& _os,const TPanel& _panel)
    {
        TPanel* pPanel;
        TIndicator* pInd;
        _os<<_panel.title().toStdString();
        for(auto e:_panel.elements)
        {
            pPanel=dynamic_cast<TPanel*>(e);
            pInd=dynamic_cast<TIndicator*>(e);
            if(pPanel)
                _os<<*pPanel;
            if(pInd)
                _os<<*pInd;

        }
        return _os;
    }

signals:

public slots:
private:
    int lineCount{1};
    QVector<QWidget*> elements;
    QGridLayout* gLayout{nullptr};
    void build();

};

#endif // TPANEL_H
