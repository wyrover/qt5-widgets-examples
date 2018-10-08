#include "widget.h"
#include "tabstackedwidget.h"
#include "tabwidget.h"
#include "tabbar.h"
#include "combotabbar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QPushButton>



Widget::Widget(QWidget *parent)
    : BrowserWindow(parent)
    
{
    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    auto top_layout = new QVBoxLayout;
    auto bottom_layout = new QHBoxLayout;

    tabWidget_ = new TabWidget(this);

    //tabWidget_ = new TabStackedWidget;

    //tabbar_ = new ComboTabBar;
    //tabWidget_->setTabBar(tabbar_);

    top_layout->addWidget(tabWidget_->tabBar());
    top_layout->addWidget(tabWidget_);
 


    auto button1 = new QPushButton(tr("test1"));
    auto button2 = new QPushButton(tr("test2"));
   

    bottom_layout->addWidget(button1);
    bottom_layout->addWidget(button2);
    layout->addLayout(top_layout);
    layout->addLayout(bottom_layout);
    layout->setStretch(0, 99);
    
    setLayout(layout);

    static int j = 0;
    connect(button1, &QPushButton::clicked, [=]() {
        
        QString tab_text(QString("tab_%1").arg(++j));
        auto textEdit1 = new QTextEdit;
        tabWidget_->addTab(textEdit1, tab_text);
    });

    connect(button2, &QPushButton::clicked, [=]() {
        auto textEdit1 = new QTextEdit;
        tabWidget_->addTab(textEdit1, "test2", true);
    });

    
}

Widget::~Widget()
{

}


