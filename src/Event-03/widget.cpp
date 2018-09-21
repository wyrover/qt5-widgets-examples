#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("鍵盤事件"));
    escLabel = new QLabel(this);
    ctrlVLabel = new QLabel(this);
    releaseLabel = new QLabel(this);
    escLabel->setText(tr(""));
    ctrlVLabel->setText(tr(""));
    releaseLabel->setText(tr(""));
    escLabel->setAlignment(Qt::AlignCenter);
    ctrlVLabel->setAlignment(Qt::AlignCenter);
    releaseLabel->setAlignment(Qt::AlignCenter);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(escLabel);
    mainLayout->addWidget(ctrlVLabel);
    mainLayout->addWidget(releaseLabel);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V) {
        ctrlVLabel->setText(tr("按下Ctrl+V"));
    }

    if (event->key() == Qt::Key_Escape) {
        escLabel->setText(tr("按下Esc"));
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    releaseLabel->setText(tr("按鍵釋放"));
}