#ifndef WIDGET_H
#define WIDGET_H

#include "tipwidget.h"
#include <QWidget>
#include <QVector>
#include <QIcon>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class QToolButton;
class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

   
private:
    
    void initAnimation();

private:
    QToolButton* button1_;    
    QPropertyAnimation* aniSizeChange;
    QPropertyAnimation* aniOpacityChange;
    QGraphicsOpacityEffect* effOpacity;
};

#endif // WIDGET_H
