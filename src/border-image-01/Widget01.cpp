#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget01.h"
#include <QVBoxLayout>
#include <QPushButton>


Widget01::Widget01(QWidget *parent)
    : QWidget(parent)
{
  
    auto layout = new QVBoxLayout;

    auto button1 = new QPushButton();    
    button1->setObjectName("button1");
    button1->setToolTip(tr("button1"));


    auto button2 = new QPushButton();
    button2->setObjectName("button2");
    button2->setToolTip(tr("button2"));


    auto button3 = new QPushButton();
    button3->setObjectName("button3");
    button3->setToolTip(tr("button3"));



    auto button4 = new QPushButton(tr("搜索答案"));
    button4->setObjectName("button4");
    button4->setToolTip(tr("button4"));

    auto button5 = new QPushButton(tr("我要提问"));
    button5->setObjectName("button5");
    button5->setToolTip(tr("button5"));

    auto button6 = new QPushButton();
    button6->setObjectName("button6");
    button6->setToolTip(tr("button6"));


    auto button7 = new QPushButton();
    button7->setObjectName("button7");
    button7->setToolTip(tr("button7"));


    auto button8 = new QPushButton();
    button8->setObjectName("button8");
    button8->setToolTip(tr("button8"));

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    layout->addWidget(button6);
    layout->addWidget(button7);
    layout->addWidget(button8);
    setLayout(layout);


    this->setMinimumSize(800, 600);
}

Widget01::~Widget01()
{
   

}