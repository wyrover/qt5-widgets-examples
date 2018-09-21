#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "mainwindow.h"


    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("QDockWidget"));
    textMain = new QTextEdit(this);
    textMain->setText(tr("這是主視窗的內容部分"));
    setCentralWidget(textMain);
    text1 = new QTextEdit(this);
    text1->setText(tr("附屬視窗1的內容部分"));
    dock1 = new QDockWidget(tr("附屬視窗1"), this);
    dock1->setFeatures(QDockWidget::AllDockWidgetFeatures); //設定元件移動、關閉、浮動的特性，本例皆可
    dock1->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea); //可在主窗口的左或右停靠
    dock1->setWidget(text1);
    addDockWidget(Qt::RightDockWidgetArea, dock1);
    text2 = new QTextEdit(this);
    text2->setText(tr("附屬視窗2的內容部分"));
    dock2 = new QDockWidget(tr("附屬視窗2"), this);
    dock2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock2->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    dock2->setWidget(text2);
    addDockWidget(Qt::RightDockWidgetArea, dock2);
}