#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QTextEdit>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private:
    QDockWidget *dock1;
    QDockWidget *dock2;
    QTextEdit *textMain;
    QTextEdit *text1;
    QTextEdit *text2;
};

#endif