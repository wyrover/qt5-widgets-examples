#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"
#include "tooltip.h"
#include "VLDFpopupmessage.h"
#include "CToastLabel.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QVariant>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QPropertyAnimation>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout;
   

    auto button2 = new QPushButton(tr("TestButton"));


    /*  auto widget_tip = new QWidget;
      widget_tip->setObjectName("widget_tip");
      widget_tip->setFixedWidth(660);

      auto tip_layout = new QVBoxLayout;*/

    auto info = new QLabel(tr("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试"));
    info->setObjectName("info");
    info->setMaximumWidth(660);
    info->setAlignment(Qt::AlignTop);
    info->adjustSize();
    info->setWordWrap(true);
    /*  tip_layout->addWidget(info);

      widget_tip->setLayout(tip_layout);*/
   
    //widget_tip->setFixedSize(200, 100);


    //widget_tip->setFixedHeight(info->height() + 20);


    tip_ = new ToolTip;

    /* connect(button2, &QPushButton::clicked, [=](bool checked) {
         ToolTip* tip = new ToolTip;
         tip->show();
         tip->move(QCursor::pos());

     });*/


    /*   connect(button2, &QPushButton::mouseMoveEvent, [=]() {
       });*/


    button2->installEventFilter(this);


    auto label2 = new QLabel(tr("ddddddddddd"));
    label2->installEventFilter(this);

    
    qDebug() << info->width() << ":" << info->height();


    auto button3 = new QPushButton("test2");
    connect(button3, &QPushButton::clicked, [=]() {
        VLDFPopupMessage* pop = new VLDFPopupMessage(this);
        const QPoint globalPos = button3->mapTo(this, QPoint(0, 0));
        pop->move(globalPos.x(), globalPos.y() - pop->height());
        pop->raise();

        pop->setMessage(tr("test111111111111111111111111111111111111111111"));
        pop->show();
    });

    auto button4 = new QPushButton("test3");
    connect(button4, &QPushButton::clicked, [=]() {
        CToastLabel* pToast = new CToastLabel("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试");
        pToast->popup(this);
    });

   
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(info);
    layout->addWidget(label2);
    layout->addStretch();
    setLayout(layout);
}

Widget::~Widget()
{
}

bool Widget::eventFilter(QObject *AObject, QEvent *AEvent)
{
    if (AEvent->type() == QEvent::MouseMove) {
        //qDebug() << "HoverMove";
    } else if (AEvent->type() == QEvent::Enter) {
        qDebug() << "HoverEnter";
        qDebug() << QCursor::pos();
        tip_->setText(tr("测试1234"));
        tip_->show();

        QPoint pos = QCursor::pos();
        pos.setX(pos.x() - 20);
        pos.setY(pos.y() - 160);
        tip_->move(pos);


        QPropertyAnimation *animation = new QPropertyAnimation(tip_, "windowOpacity");
        animation->setDuration(500);
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start();
    } else if (AEvent->type() == QEvent::Leave) {
        qDebug() << "HoverLeave";

        QPropertyAnimation *animation = new QPropertyAnimation(tip_, "windowOpacity");
        animation->setDuration(1000);
        animation->setStartValue(1);
        animation->setEndValue(0);
        animation->start();
        //tip_->hide();
    }

    return QWidget::eventFilter(AObject, AEvent);
}

