#ifndef WIDGET_H
#define WIDGET_H

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
private:
    QToolButton* createSidebarButton(const QString& iconPath, const QString& title);

private:
    QToolButton* button1_;
    QVector<QIcon> icons_;
    QVector<QIcon> selected_icons_;
    QTimer* timer_;
};

#endif // WIDGET_H
