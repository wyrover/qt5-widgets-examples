#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("事件過濾器"));
    upLineEdit = new QLineEdit(this);
    downLineEdit = new QLineEdit(this);
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(upLineEdit);
    mainLayout->addWidget(downLineEdit);
    upLineEdit->installEventFilter(this);
    downLineEdit->installEventFilter(this);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == upLineEdit || obj == downLineEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            if (keyEvent->key() == Qt::Key_Up) {
                upLineEdit->setText(tr("Up鍵被按下"));
                downLineEdit->setText(tr(""));
                return true;
            }

            if (keyEvent->key() == Qt::Key_Down) {
                upLineEdit->setText(tr(""));
                downLineEdit->setText(tr("Down鍵被按下"));
                return true;
            }
        } else {
            return QWidget::eventFilter(obj, event);
        }
    } else {
        return QWidget::eventFilter(obj, event); //對於不關心的事件，返回父類的eventFilter()函數
    }
}