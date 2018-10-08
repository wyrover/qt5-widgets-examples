#include "widget.h"
#include "tabwidget.h"
#include <QVBoxLayout>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);


    tabWidget_ = new TabWidget;

    tabWidget_->addTab(new QLabel(tr("test1")), tr("test1"));
    tabWidget_->addTab(new QLabel(tr("test2")), tr("test2"));
    tabWidget_->addTab(new QLabel(tr("test3")), tr("test3"));

    layout->addWidget(tabWidget_);


    setLayout(layout);
}

Widget::~Widget()
{

}
