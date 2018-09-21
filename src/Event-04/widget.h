#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QLineEdit>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);
private:
    QLineEdit *upLineEdit;
    QLineEdit *downLineEdit;
    QVBoxLayout *mainLayout;
};

#endif