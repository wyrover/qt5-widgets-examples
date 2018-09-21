#ifndef DEMO_WIDGET_H
#define DEMO_WIDGET_H

#include <QWidget>

namespace Ui
{
class DemoWidget;
}

class DemoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DemoWidget(QWidget *parent = 0);
    ~DemoWidget();

private:
    Ui::DemoWidget *ui;
};

#endif // DEMO_WIDGET_H
