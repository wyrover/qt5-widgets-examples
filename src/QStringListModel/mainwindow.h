#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QStringListModel *model;
    QListView *listView;

private slots:
    void insertData();
    void deleteData();
    void showData();
};

#endif // MAINWINDOW_H
