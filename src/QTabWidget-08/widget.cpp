#include "widget.h"
#include "ComboTabBar.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    
{
    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);


    auto tabbar = new ComboTabBar;
    tabbar->addTab("tab1");
    tabbar->addTab("tab2");
    tabbar->addTab("tab3");
    tabbar->addTab("tab4");
    

    layout->addWidget(tabbar);
    setLayout(layout);

    
}

Widget::~Widget()
{

}


