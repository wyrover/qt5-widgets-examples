// https://www.cnblogs.com/lvdongjie/p/4813572.html
#include "mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList data;
    data << "项目 A" << "项目 B" << "项目 C";
    model = new QStringListModel(this);
    model->setStringList(data);
    listView = new QListView(this);
    listView->setModel(model);
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    QPushButton *pushButton_insert = new QPushButton("插入", this);
    connect(pushButton_insert, SIGNAL(clicked()), this, SLOT(insertData()));
    QPushButton *pushButton_delete = new QPushButton("删除", this);
    connect(pushButton_delete, SIGNAL(clicked()), this, SLOT(deleteData()));
    QPushButton *pushButton_show = new QPushButton("显示", this);
    connect(pushButton_show, SIGNAL(clicked()), this, SLOT(showData()));
    hboxLayout->addWidget(pushButton_insert);
    hboxLayout->addWidget(pushButton_delete);
    hboxLayout->addWidget(pushButton_show);
    QWidget *widget = new QWidget;
    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(listView);
    vboxLayout->addLayout(hboxLayout);
    widget->setLayout(vboxLayout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::insertData()
{
    bool ok;
    QString text = QInputDialog::getText(this, "插入数据", "请输入数据：", QLineEdit::Normal, "新数据", &ok);

    if (ok) {
        int row = listView->currentIndex().row();
        qDebug() << row;

        if (row == -1) row = 0;

        model->insertRows(row, 1);
        QModelIndex index = model->index(row);
        model->setData(index, text);
        listView->setCurrentIndex(index);
        //listView->edit(index);    // 激活编辑
    }
}

void MainWindow::deleteData()
{
    if (model->rowCount() > 0) {
        model->removeRows(listView->currentIndex().row(), 1);
    }
}

void MainWindow::showData()
{
    QStringList data = model->stringList();
    QString str;

    foreach (QString s, data) {
        str += s + "\n";
    }

    QMessageBox::information(this, "数据", str);
}
