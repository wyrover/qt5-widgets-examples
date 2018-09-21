#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

#include <QtPlugin>

#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif


class EventLabel : public QLabel
{
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

void EventLabel::mouseMoveEvent(QMouseEvent *event)
{
    QString msg;
    msg.sprintf("<center><h1>Move: (%d, %d)</h1></center>",
                event->x(), event->y());
    this->setText(msg);
}

void EventLabel::mousePressEvent(QMouseEvent *event)
{
    QString msg;
    msg.sprintf("<center><h1>Press: (%d, %d)</h1></center>",
                event->x(), event->y());
    this->setText(msg);
}

void EventLabel::mouseReleaseEvent(QMouseEvent *event)
{
    QString msg;
    msg.sprintf("<center><h1>Release: (%d, %d)</h1></center>",
                event->x(), event->y());
    this->setText(msg);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EventLabel *label = new EventLabel;
    label->setWindowTitle("MouseEvent Demo");
    label->resize(300, 200);
    label->show();
    return app.exec();
}


