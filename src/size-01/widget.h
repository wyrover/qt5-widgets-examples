#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


class QToolButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QToolButton* createSidebarButton(const QString& iconPath, const QString& title);
};

#endif // WIDGET_H
