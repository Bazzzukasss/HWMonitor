#include "tpanel.h"

TPanel::TPanel(QWidget *parent) :
    QGroupBox(parent)
{
    build();
}

TPanel::~TPanel()
{
    for(auto el:elements)
        delete el;
}

void TPanel::build()
{
    int i(0),r(0),c(0),maxR(0),maxC(0);
    this->setAlignment(Qt::AlignHCenter);
    if(gLayout!=nullptr) delete gLayout;
        gLayout = new QGridLayout(this);
    gLayout->setSpacing(2);
    gLayout->setMargin(2);
    for(auto el:elements)
    {
        c=i/lineCount;
        r=i%lineCount;
        gLayout->addWidget(el,r,c);
        i++;
        if(maxR<r)maxR=r;
        if(maxC<c)maxC=c;
    }
    gLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::Expanding),maxR+1,c);
    //gLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum),0,maxC+1);
}

QWidget* TPanel::addElement(QWidget *_element)
{
    elements.push_back(_element);
    build();
    return _element;
}

void TPanel::setLineCount(int _line_count)
{
    lineCount = _line_count;
    build();
}

QVector<QWidget*>&  TPanel::getElements()
{
    return elements;
}
