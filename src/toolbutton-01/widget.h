#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QIcon>

class QToolButton;
class QTabBar;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    

private:
    QTabBar* tabbar_;
};

#endif // WIDGET_H
