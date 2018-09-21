#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"
#include "qgradualbox.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QVariant>
#include <QTimer>
#include <QDebug>
#include <QPushButton>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName("demo");
    auto layout = new QVBoxLayout;



    


    auto button2 = new QPushButton(tr("启用"));
    button2->setCheckable(true);

    connect(button2, &QPushButton::toggled, [=](bool checked) {
        if (checked) {
            this->showTipWidget(tr("测试消息"));
            button2->setText(tr("停用"));
        }
        else {
           
            button2->setText(tr("启用"));
        }
    });


    auto button3 = new QPushButton(tr("QGradualBox"));
    connect(button3, &QPushButton::clicked, [=](bool) {
        auto gradualBox = new QGradualBox(tr("测试一下"));
        gradualBox->show();
    });




    tipWidget_ = new TipWidget("Hello, Milis!", this);
    tipWidget_->setFixedHeight(30);
    tipWidget_->move(10, 10);
    tipWidget_->hide();

    tip_timer_ = new QTimer(this);
    connect(tip_timer_, &QTimer::timeout, this, &Widget::hideTipWidget);
    tip_timer_->setInterval(2000);

 
    layout->addWidget(button2);
    layout->addWidget(button3);
    setLayout(layout);

    resize(800, 600);
}

Widget::~Widget()
{
    if (tip_timer_ != NULL) {
        disconnect(tip_timer_, &QTimer::timeout, this, &Widget::hideTipWidget);
        if (tip_timer_->isActive()) {
            tip_timer_->stop();
        }        
    }
}


void Widget::showTipWidget(const QString text)
{
    if (this->tipWidget_->isVisible())
        this->tipWidget_->hide();
    if (tip_timer_->isActive())
        tip_timer_->stop();
    tip_timer_->start();
    //    this->tipWidget->move(this->pos().x() + 30, this->pos().y() + TOP_TOOLBAR_HEIGHT);
    this->tipWidget_->setText(text);
    this->tipWidget_->show();
}

void Widget::hideTipWidget()
{
    this->tipWidget_->hide();
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
