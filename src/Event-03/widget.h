#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QKeyEvent>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QLabel *escLabel;
    QLabel *ctrlVLabel;
    QLabel *releaseLabel;
    QVBoxLayout *mainLayout;
};

#endif