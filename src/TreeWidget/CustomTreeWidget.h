#pragma once

#include <QTreeWidget>

class CustomTreeWidget: public QTreeWidget
{
    Q_OBJECT
public:
    CustomTreeWidget(QWidget * parent = 0);
    ~CustomTreeWidget();
private slots:
    void itemSelectionChangedSlot();
};