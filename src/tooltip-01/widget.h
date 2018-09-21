#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QIcon>

class QToolButton;
class QTimer;

class ToolTip;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    bool eventFilter(QObject *AObject, QEvent *AEvent);

private:
    ToolTip* tip_;
};

#endif // WIDGET_H
