#include "wheel.h"

#include <QWheelEvent>

WheelHelper::WheelHelper()
{
}

void WheelHelper::reset()
{
    m_wheelDelta = 0;
    m_directions.clear();
}

void WheelHelper::processEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().x() ? event->angleDelta().x() : event->angleDelta().y();
    bool directionY = delta == event->angleDelta().y();

    // When scroll to both directions, prefer the major one
    if (event->angleDelta().x() && event->angleDelta().y()) {
        if (qAbs(event->angleDelta().y()) > qAbs(event->angleDelta().x())) {
            delta = event->angleDelta().y();
            directionY = true;
        } else {
            delta = event->angleDelta().x();
            directionY = false;
        }
    }

    // Reset when direction changes
    if ((delta < 0 && m_wheelDelta > 0) || (delta > 0 && m_wheelDelta < 0)) {
        m_wheelDelta = 0;
    }

    m_wheelDelta += delta;

    // Angle delta 120 for common "one click"
    // See: http://qt-project.org/doc/qt-5/qml-qtquick-wheelevent.html#angleDelta-prop
    while (m_wheelDelta >= 120) {
        m_wheelDelta -= 120;
        if (directionY) {
            m_directions.enqueue(WheelUp);
        } else {
            m_directions.enqueue(WheelLeft);
        }
    }
    while (m_wheelDelta <= -120) {
        m_wheelDelta += 120;
        if (directionY) {
            m_directions.enqueue(WheelDown);
        } else {
            m_directions.enqueue(WheelRight);
        }
    }
}

WheelHelper::Direction WheelHelper::takeDirection()
{
    return m_directions.isEmpty() ? None : m_directions.dequeue();
}