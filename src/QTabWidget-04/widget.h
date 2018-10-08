#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMdiArea>

class TabWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    void newThread();

private:
    

    QMdiArea mMdiArea;
};

#endif // WIDGET_H
