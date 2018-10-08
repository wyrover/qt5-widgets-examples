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
    void slotPopSignalWnd(int nIndex);

private:
    void newThread();



private:
    
    DragInOutTabWidget* tabWidget_;
    QMap<QString, QWidget*> m_widgets;
};

#endif // WIDGET_H
