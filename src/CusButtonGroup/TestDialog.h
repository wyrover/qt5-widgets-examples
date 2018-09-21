#pragma once

#include <QDialog>

class CusButtonGroup;
namespace Ui
{
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT
public:
    TestDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
    virtual ~TestDialog();
private:
    Ui::TestDialog*     m_ui;
    CusButtonGroup*     m_cusButtonGroup;
};