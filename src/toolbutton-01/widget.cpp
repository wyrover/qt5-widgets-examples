#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"

#include <QVBoxLayout>
#include <QToolButton>
#include <QVariant>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QTabBar>
#include <QTabWidget>
#include <QPropertyAnimation>
#include <QStyle>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout;
    tabbar_ = new QTabBar;
    tabbar_->setMovable(true);
    //tabbar_->setDocumentMode(true);
    tabbar_->setTabsClosable(true);

    for (int i = 1; i <= 20; ++i) {
        tabbar_->addTab(QString(tr("新建标签页 %1")).arg(i));
    }


   

    //for (int i = 0; i < tabbar_->count(); ++i) {
    //    QWidget* closeButton = tabbar_->tabButton(i, (QTabBar::ButtonPosition)style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, 0, tabbar_));
    //    if (closeButton) {
    //        if (closeButton->objectName() == QLatin1String("combotabbar_tabs_close_button")) {
    //            continue;
    //        }
    //    }


    //    //QAbstractButton* closeButton = new QPushButton(this);
    //    //closeButton->setFixedSize(closeButtonSize());
    //    ////closeButton->setToolTip(m_closeButtonsToolTip);
    //    ////connect(closeButton, SIGNAL(clicked()), this, SLOT(closeTabFromButton()));
    //    //m_mainTabBar->setTabButton(index, closeButtonPosition(), closeButton);

    //    //insertCloseButton(i + pinnedTabsCount());
    //    if (closeButton) {
    //        closeButton->deleteLater();
    //    }
    //}

    


    auto tabwidget_ = new QTabWidget;
    
    //tabwidget_->tabBar()->setMovable(true);
    auto tabbar = tabwidget_->tabBar();
    for (int i = 1; i <= 10; ++i) {
        tabbar->addTab(QString(tr("新建标签页 %1")).arg(i));
    }

    layout->addWidget(tabbar_);
    layout->addWidget(tabwidget_);
   
    setLayout(layout);
}

Widget::~Widget()
{
}



