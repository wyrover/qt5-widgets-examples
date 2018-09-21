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

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout;
    button1_ = createSidebarButton(":/assets/images/log/1.svg", tr("参数"));


    for (unsigned int i = 1; i <= 7; ++i) {
        QIcon svgIcon(QString(":/assets/images/log/%1.svg").arg(i));       
        QIcon icon;
        icon.addPixmap(svgIcon.pixmap(40, 40), QIcon::Normal);
        icon.addPixmap(svgIcon.pixmap(40, 40), QIcon::Disabled);
        icons_.push_back(icon);

        QIcon svgIcon2(QString(":/assets/images/log_selected/%1.svg").arg(i));
        QIcon icon2;
        icon2.addPixmap(svgIcon2.pixmap(40, 40), QIcon::Normal);
        icon2.addPixmap(svgIcon2.pixmap(40, 40), QIcon::Disabled);

        selected_icons_.push_back(icon2);
    }



    timer_ = new QTimer(this);
    //timer_->start(200);

    static unsigned int i = 0;
    connect(timer_, &QTimer::timeout, [=]() {
        if (button1_->isChecked())
            button1_->setIcon(selected_icons_[i]);
        else
            button1_->setIcon(icons_[i]);

        if (i == 6)
            i = 0;
        else
            i++;
    });


    auto button2 = new QPushButton(tr("启用"));
    button2->setCheckable(true);

    connect(button2, &QPushButton::toggled, [=](bool checked) {
        if (checked) {
            timer_->start(200);
            button2->setText(tr("停用"));
        }
        else {
            timer_->stop();
            button2->setText(tr("启用"));
        }
    });



    layout->addWidget(button1_);
    layout->addWidget(button2);
    setLayout(layout);
}

Widget::~Widget()
{
}


QToolButton* Widget::createSidebarButton(const QString& iconPath, const QString& title)
{
    QToolButton * btn = new QToolButton;
    btn->setIconSize(QSize(40, 40));
    btn->setText(title);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setFixedSize(84, 75);   
    btn->setCheckable(true);
    btn->setAutoRaise(false);
    btn->setProperty("default_icon", iconPath);
    QIcon svgIcon(iconPath);
    QIcon icon;
    icon.addPixmap(svgIcon.pixmap(40, 40), QIcon::Normal);
    icon.addPixmap(svgIcon.pixmap(40, 40), QIcon::Disabled);
    btn->setIcon(icon);
    return btn;
   
}
