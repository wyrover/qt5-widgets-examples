#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool event(QEvent* event);

private:
    void init();

private slots:
    void clickedSlot(bool);

private:
    Ui::MainWindow *    m_ui;
};

#endif // MAINWINDOW_H
