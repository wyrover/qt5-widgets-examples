#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>

class DragInOutTabWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    

private:
    void newThread();



private:
    
    
};

#endif // WIDGET_H
