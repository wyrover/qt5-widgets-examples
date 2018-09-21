#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(style()->standardPixmap(QStyle::SP_TitleBarMenuButton)));
    //showMaximized();
    addItem("");
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(addItem(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addItem(QString s)
{
    ui->listWidget->clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QStyle::StandardPixmap>();

    for (qint32 i = 0, count = metaEnum.keyCount(); i < count; i++) {
        if (QString(QLatin1String(metaEnum.key(i))).contains(s, Qt::CaseInsensitive)) {
            QStyle::StandardPixmap SP = (QStyle::StandardPixmap)metaEnum.keyToValue(metaEnum.key(i));
            QListWidgetItem *LWI = new QListWidgetItem(QIcon(style()->standardPixmap(SP)), metaEnum.key(i));
            //LWI->setSizeHint(QSize(150,150));
            ui->listWidget->addItem(LWI);
        }
    }
}