#ifndef WIDGET_H
#define WIDGET_H

#include "browserwindow.h"
#include <QWidget>
#include <QMap>

class TabStackedWidget;
class ComboTabBar;

class TabWidget;
class MyTabBar;

class Widget : public BrowserWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
   

private:
    void newThread();



private:
    TabWidget* tabWidget_;
    MyTabBar* tabbar_;
};

#endif // WIDGET_H
