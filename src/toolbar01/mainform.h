#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

class QVBoxLayout;

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:
    void onToolbarClicked(bool checked);

private:
    void create_svg_toolbar();
private:
    QVBoxLayout* layout_;
};

#endif // MAINFORM_H
