#ifndef wheel_h__
#define wheel_h__

#include <QQueue>

class QScrollArea;
class QPropertyAnimation;
class QHBoxLayout;

class TabBarScrollWidget;
class TabBarHelper;
class ToolButton;

class QWheelEvent;

class WheelHelper
{
public:
    enum Direction {
        None = 0,
        WheelUp,
        WheelDown,
        WheelLeft,
        WheelRight
    };

    explicit WheelHelper();

    void reset();
    void processEvent(QWheelEvent *event);
    Direction takeDirection();

private:
    int m_wheelDelta = 0;
    QQueue<Direction> m_directions;
};


#endif // wheel_h__
