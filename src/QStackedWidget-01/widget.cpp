#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("StackedWidget"));
    listWidget = new QListWidget(this);
    listWidget->insertItem(0, tr("第一項"));
    listWidget->insertItem(1, tr("第二項"));
    listWidget->insertItem(2, tr("第三項"));
    label1 = new QLabel(tr("第一項的內容"));
    label2 = new QLabel(tr("第二項的內容"));
    label3 = new QLabel(tr("第三項的內容"));
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(label1);
    stackedWidget->addWidget(label2);
    stackedWidget->addWidget(label3);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(stackedWidget, 0, Qt::AlignHCenter);
    mainLayout->setStretchFactor(listWidget, 1);   //伸縮時左右分別為1：4拉伸
    mainLayout->setStretchFactor(stackedWidget, 4);
    connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
}