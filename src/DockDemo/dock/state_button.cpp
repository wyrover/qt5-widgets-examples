#include "state_button.h"

#include <QPainter>
#include <QApplication>
#include <QMouseEvent>


StateButton::StateButton(QWidget* parent):
    QWidget(parent),
    state(BTN_NORMAL),
    pressed(false),
    pressedInside(false)
{
    setMouseTracking(true);
}

void StateButton::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        bool inside = contains(event->pos());
        pressed = true;
        pressedInside = pressed && inside;
        updateState(inside);
        event->accept();
    }
}

void StateButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        bool inside = contains(event->pos());

        if (inside && pressedInside) {
            emit clicked();
        }

        pressed = false;
        updateState(isVisible() && inside); // reset state if closed on clicked event
        event->accept();
    }
}

void StateButton::mouseMoveEvent(QMouseEvent* event)
{
    updateState(contains(event->pos()));
    event->accept();
}

void StateButton::enterEvent(QEvent* event)
{
    updateState(true);
    event->accept();
}

void StateButton::leaveEvent(QEvent* event)
{
    updateState(false);
    event->accept();
}

void StateButton::updateState(bool inside)
{
    ButtonState newState;

    if (inside) {
        if (pressed || qApp->mouseButtons() & Qt::LeftButton) {
            if (pressedInside)
                newState = BTN_PRESSED;
            else
                newState = BTN_NORMAL;
        } else {
            newState = BTN_HOVER;
        }
    } else {
        newState = BTN_NORMAL;
    }

    if (newState != state) {
        state = newState;
        repaint();
    }
}

bool StateButton::contains(const QPoint &pos)
{
    return rect().contains(pos);
}
