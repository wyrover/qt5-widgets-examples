#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
private:
    QTabWidget *tabWidget;
    QVBoxLayout *mainLayout;
};

#endif