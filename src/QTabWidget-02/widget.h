#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class TabWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    TabWidget* tabWidget_;
};

#endif // WIDGET_H
