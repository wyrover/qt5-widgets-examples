#ifndef QTABLEWIDGET_TEST_H
#define QTABLEWIDGET_TEST_H

#include <QtWidgets/QDialog>
#include "ui_qtablewidget_test.h"

class QTableWidget_test : public QDialog
{
    Q_OBJECT

public:
    QTableWidget_test(QWidget *parent = 0);
    ~QTableWidget_test();

private:
    Ui::QTableWidget_testClass ui;
};

#endif // QTABLEWIDGET_TEST_H
