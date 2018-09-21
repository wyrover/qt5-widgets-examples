#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
private:
    QHBoxLayout *mainLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};

#endif