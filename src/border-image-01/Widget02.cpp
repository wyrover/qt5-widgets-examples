#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget02.h"
#include <QVBoxLayout>
#include <QPushButton>


Widget02::Widget02(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("Widget02");
  
    auto layout = new QVBoxLayout;

    auto button9 = new QPushButton();    
    button9->setObjectName("button9");
    button9->setToolTip(tr("button9"));


    auto button10 = new QPushButton();
    button10->setObjectName("button10");
    button10->setToolTip(tr("button10"));


    auto button11 = new QPushButton();
    button11->setObjectName("button11");
    button11->setToolTip(tr("button11"));


    auto buttonMin = new QPushButton;
    buttonMin->setObjectName("buttonMin");

    auto buttonMax = new QPushButton;
    buttonMax->setObjectName("buttonMax");

    auto buttonRestore = new QPushButton;
    buttonRestore->setObjectName("buttonRestore");
    

    auto buttonClose = new QPushButton;
    buttonClose->setObjectName("buttonClose");


    layout->addWidget(button9);
    layout->addWidget(button10);
    layout->addWidget(button11);
    layout->addWidget(buttonMin);
    layout->addWidget(buttonMax);
    layout->addWidget(buttonRestore);
    layout->addWidget(buttonClose);
   
    setLayout(layout);


    //this->setMinimumSize(800, 600);
}

Widget02::~Widget02()
{
   

}