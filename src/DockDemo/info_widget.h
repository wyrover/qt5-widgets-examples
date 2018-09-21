#pragma once

#include <QWidget>

namespace Ui
{
class InfoWidget;
}

class InfoWidget :
    public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = 0);
    ~InfoWidget();

public:
    void paintEvent(QPaintEvent*);

private:
    Ui::InfoWidget *ui;
};
