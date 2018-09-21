#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UiTableWidgetItem.h"
#include "UiTableWidgetItemSecond.h"
#include "DataTableWidgetEditorDelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

bool MainWindow::event(QEvent* event)
{
    QEvent::Type type = event->type();

    if (event->type() == QEvent::HoverEnter) {
        int i = 0;
        ++i;
    }

    if (type != QEvent::WindowActivate | QEvent::Paint) {
        int i = 0;
        ++i;
    }

    if (type == QEvent::MouseMove) {
        int i = 0;
        ++i;
    }

    return QWidget::event(event);
}

void MainWindow::init()
{
    connect(m_ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(clickedSlot(bool)));
    QTreeWidgetItem *___qtreewidgetitem1 = m_ui->treeWidget2->topLevelItem(0);
    m_ui->treeWidget2->setItemWidget(___qtreewidgetitem1, 0, new UiTableWidgetItem(this));
    //m_ui->treeWidget2->setItemWidget(___qtreewidgetitem1, 1, new UiTableWidgetItemSecond(this));
    //DataTableWidgetEditorDelegate* delegateType = new DataTableWidgetEditorDelegate(m_ui->treeWidget,this);
    //m_ui->treeWidget->setItemDelegate(delegateType);
    //m_ui->treeWidget->openPersistentEditor(___qtreewidgetitem1);
}

void MainWindow::clickedSlot(bool)
{
    QList<QTreeWidgetItem*> listItem = m_ui->treeWidget3->selectedItems();

    for (int i = 0; i < listItem.size(); ++i) {
        //m_ui->treeWidget3->removeItemWidget(listItem[i], 0);
        delete listItem[i];
    }
}
