#ifndef WIDGET_H
#define WIDGET_H

#include "tipwidget.h"
#include <QWidget>
#include <QVector>
#include <QIcon>

class QToolButton;
class QTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    void showTipWidget(const QString text);
    void hideTipWidget();
private:
    QToolButton* createSidebarButton(const QString& iconPath, const QString& title);

private:
    QToolButton* button1_;
    QVector<QIcon> icons_;
    QVector<QIcon> selected_icons_;
    QTimer* timer_;
    TipWidget* tipWidget_;
    QTimer* tip_timer_;
};

#endif // WIDGET_H
