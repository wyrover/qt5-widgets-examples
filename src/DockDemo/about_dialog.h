#pragma once

#include <QDialog>

namespace Ui
{
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;

private Q_SLOTS:
    void updateTheme();
};

void showAbout(QWidget* parent = NULL);
