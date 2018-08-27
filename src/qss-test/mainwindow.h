#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QThread>

class Worker : public QObject {
    Q_OBJECT
public:
    Worker();
    ~Worker();

    void setStyle(const char* filename);

Q_SIGNALS:
    void onChange(const QString& filename);


public slots:
    void doWork();
};


class QTableWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    

private slots:
    void on_actionExit_triggered();
    void onChange(const QString& filename);


private:
    void watch_dir();

    void createWidget00(int row);
    void createWidget01(int row);
    void createWidget02(int row);
    void createWidget03(int row);
    void createWidget04(int row);
    void createWidget05(int row);
    void createWidget06(int row);
    void createWidget07(int row);
    void createWidget08(int row);
    void createWidget09(int row);
    void createWidget10(int row);
    void createWidget11(int row);
    void createWidget12(int row);
    void createWidget13(int row);
    void createWidget14(int row);
    void createWidget15(int row);
    void createWidget16(int row);
    void createWidget17(int row);
    void createWidget18(int row);
    void createWidget19(int row);
    void createWidget20(int row);
    void createWidget21(int row);
    void createWidget22(int row);
    void createWidget23(int row);
    void createWidget24(int row);
    void createWidget25(int row);
    void createWidget26(int row);
    void createWidget27(int row);

private:   
    Worker* worker_;
    QThread* thread_;
    QTableWidget* table_;
};

#endif // MAINWINDOW_H
