#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QEvent>
#include <QKeyEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    bool event(QEvent *e);
private:
    QLabel *upLabel;
    QLabel *downLabel;
    QVBoxLayout *mainLayout;
};

#endif