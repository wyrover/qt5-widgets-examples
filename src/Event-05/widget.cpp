#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("event事件"));
    upLabel = new QLabel(this);
    downLabel = new QLabel(this);
    upLabel->setText(tr(""));
    downLabel->setText(tr(""));
    upLabel->setAlignment(Qt::AlignCenter);      //label文字置中
    downLabel->setAlignment(Qt::AlignCenter);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(upLabel);
    mainLayout->addWidget(downLabel);
}
bool Widget::event(QEvent *e)
{
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);

        if (keyEvent->key() == Qt::Key_Up) {
            upLabel->setText(tr("Up鍵被按下"));
            downLabel->setText(tr(""));
            return true;
        }

        if (keyEvent->key() == Qt::Key_Down) {
            downLabel->setText(tr("Down鍵被按下"));
            upLabel->setText(tr(""));
            return true;
        }
    }

    return QWidget::event(e); //對於其它不關心的事件，調用父類的event()函數繼續轉發
}