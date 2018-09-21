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
    initAnimation();

    this->setObjectName("demo");
    auto layout = new QVBoxLayout;

    auto button2 = new QPushButton(tr("启用"));
    button2->setCheckable(true);

    resize(800, 600);

    connect(button2, &QPushButton::toggled, [=](bool checked) {
        if (checked) {           
            aniSizeChange->setEndValue(QRect(this->x(), this->y()+200, this->width(), 600));
            aniSizeChange->start();

            aniOpacityChange->setStartValue(0.1);
            aniOpacityChange->setEndValue(0.99);        // cant use 1.0??
            aniOpacityChange->start();

            button2->setText(tr("停用"));
        }
        else {          
            aniSizeChange->setEndValue(QRect(this->x(), this->y()-200, this->width(), 600));
            aniSizeChange->start();

            aniOpacityChange->setStartValue(1.0);
            aniOpacityChange->setEndValue(0.1);
            aniOpacityChange->start();

            button2->setText(tr("启用"));
        }
    });  

 
    layout->addWidget(button2);
    
    setLayout(layout);

    
}

Widget::~Widget()
{
    delete aniOpacityChange;
    delete aniSizeChange;


}


void Widget::initAnimation()
{
    aniSizeChange = new QPropertyAnimation(this, "geometry");
    aniSizeChange->setDuration(500);
    aniSizeChange->setEasingCurve(QEasingCurve::OutCirc);

    effOpacity = new QGraphicsOpacityEffect();
    effOpacity->setOpacity(0.5);
    this->setGraphicsEffect(effOpacity);

    aniOpacityChange = new QPropertyAnimation(effOpacity, "opacity");
    aniOpacityChange->setDuration(500);
    aniOpacityChange->setEasingCurve(QEasingCurve::InCirc);
}
