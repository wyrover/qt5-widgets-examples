#include "titlebar_close_button.h"

#include <QPainter>


static const int CrossPadding = 4;
static const QColor CloseBackColorNormal = Qt::gray;
static const QColor CloseLineColorNormal = Qt::lightGray;
static const QColor CloseBackColorHover = Qt::red;
static const QColor CloseLineColorHover = Qt::white;
static const QColor CloseBackColorPressed = Qt::white;
static const QColor CloseLineColorPressed = Qt::gray;


TitlebarCloseButton::TitlebarCloseButton(QWidget* parent) :
    StateButton(parent)
{
    //
}

TitlebarCloseButton::~TitlebarCloseButton()
{
    //
}

void TitlebarCloseButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect r = rect();
    static QColor colors[] {CloseBackColorNormal, CloseBackColorHover, CloseBackColorPressed};
    painter.fillRect(r, colors[buttonState()]);
    static QColor crossColors[] {CloseLineColorNormal, CloseLineColorHover, CloseLineColorPressed};
    painter.setPen(crossColors[buttonState()]);
    r.adjust(CrossPadding, CrossPadding, -CrossPadding , -CrossPadding);
    painter.drawLine(r.topLeft(), r.bottomRight());
    painter.drawLine(r.left(), r.bottom() + 1, r.right(), r.top() + 1); // fix QRect bounds bug

    if (buttonState() == BTN_HOVER) {
        painter.setPen(CloseLineColorHover);
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }
}
