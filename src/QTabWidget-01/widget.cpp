#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("QTabWidget"));
    tabWidget = new QTabWidget(this);
    QLabel *label1 = new QLabel(tr("第一項的內容"));
    QLabel *label2 = new QLabel(tr("第二項的內容"));
    QLabel *label3 = new QLabel(tr("第三項的內容"));
    tabWidget->addTab(label1, tr("第一項"));
    tabWidget->addTab(label2, tr("第二項"));
    tabWidget->addTab(label3, tr("第三項"));
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
}