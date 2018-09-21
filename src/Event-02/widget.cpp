#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("滑鼠事件"));
    moveLabel = new QLabel(this);
    pressLabel = new QLabel(this);
    doubleClickLabel = new QLabel(this);
    releaseLabel = new QLabel(this);
    moveLabel->setText(tr(""));
    pressLabel->setText(tr(""));
    doubleClickLabel->setText(tr(""));
    releaseLabel->setText(tr(""));
    moveLabel->setAlignment(Qt::AlignCenter);  //label文字置中
    pressLabel->setAlignment(Qt::AlignCenter);
    doubleClickLabel->setAlignment(Qt::AlignCenter);
    releaseLabel->setAlignment(Qt::AlignCenter);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(moveLabel);
    mainLayout->addWidget(pressLabel);
    mainLayout->addWidget(doubleClickLabel);
    mainLayout->addWidget(releaseLabel);
    //預設為false，此時要按著滑鼠才會追蹤位置，如果mouseTracking為true，則只要滑鼠在視窗範圍內就會追蹤位置
    setMouseTracking(true);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    //arg()函數可以替換掉QString中出現的佔位符。占位符為%加位置，如%1、%2。
    moveLabel->setText(QString(tr("移動到：(%1, %2)")).arg(QString::number(event->x()), QString::number(event->y())));
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    pressLabel->setText(QString(tr("點擊處：(%1, %2)")).arg(QString::number(event->x()), QString::number(event->y())));
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    doubleClickLabel->setText(QString(tr("雙擊處：(%1, %2)")).arg(QString::number(event->x()), QString::number(event->y())));
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    releaseLabel->setText(QString(tr("釋放處：(%1, %2)")).arg(QString::number(event->x()), QString::number(event->y())));
}