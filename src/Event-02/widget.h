#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMouseEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QLabel *moveLabel;
    QLabel *pressLabel;
    QLabel *doubleClickLabel;
    QLabel *releaseLabel;
    QVBoxLayout *mainLayout;
};

#endif