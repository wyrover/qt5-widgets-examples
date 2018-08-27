#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QThread>
#include <QTableWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QToolButton>
#include <QTreeWidget>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QProgressBar>
#include <QTabBar>
#include <QScrollBar>
#include <QToolTip>
#include <QTextEdit>
#include <QGroupBox>
#include <QListView>
#include <QStringListModel>
#include <QListWidget>
#include <QToolbar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <uv.h>
#include <iostream>


static uv_fs_event_t fs_event;


static void fs_event_cb_dir_multi_file_in_subdir(uv_fs_event_t* handle,
    const char* filename,
    int events,
    int status)
{
    Worker* form = (Worker*)handle->data;
    form->setStyle(filename);


    if (events == UV_CHANGE) {
        std::cout << "UV_CHANGE" << std::endl;
    }

    if (events == UV_RENAME) {
        std::cout << "UV_RENAME" << std::endl;
    }

    uv_fs_event_start(&fs_event, fs_event_cb_dir_multi_file_in_subdir, ".", UV_FS_EVENT_RECURSIVE);
}

Worker::Worker()
{

}

Worker::~Worker()
{

}

void Worker::setStyle(const char* filename)
{
    emit onChange(QString(filename));  
}

void Worker::doWork()
{
    uv_loop_t* loop;
    int r;

    /* Setup */
    loop = uv_default_loop();
    fs_event.data = (void*)this;
    r = uv_fs_event_init(loop, &fs_event);
    r = uv_fs_event_start(&fs_event, fs_event_cb_dir_multi_file_in_subdir, ".", UV_FS_EVENT_RECURSIVE);
    uv_run(loop, UV_RUN_DEFAULT);
}





MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
    
{
    //ui->setupUi(this);

    worker_ = new Worker;
    thread_ = new QThread;
    
    connect(thread_, SIGNAL(started()), worker_, SLOT(doWork()));
    connect(thread_, SIGNAL(finished()), worker_, SLOT(deleteLater()));
    connect(worker_, &Worker::onChange, this, &MainWindow::onChange, Qt::QueuedConnection);

    worker_->moveToThread(thread_);
    thread_->start();


    auto layout = new QVBoxLayout;


    table_ = new QTableWidget(40, 3);
    table_->setObjectName("platform_table");
    table_->setMinimumHeight(500);
    table_->setFocusPolicy(Qt::NoFocus);

    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    //table_->setSelectionMode(QAbstractItemView::NoSelection);
    //table_->verticalHeader()->setVisible(false);
    //table_->horizontalHeader()->setDefaultSectionSize(350);
    //table_->horizontalHeader()->setStretchLastSection(true);
    //table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table_->horizontalHeader()->setFixedHeight(50); //设置表头的高度
    
    //table_->horizontalHeader()->setClickable(false);
    QStringList header;
    header << tr("名称") << tr("交易对") << tr("操作项");
    //QStringList vertical_header;
    //vertical_header << "One" << "Two" << "Three" << "Four" << "Five" << "Six";
    table_->setHorizontalHeaderLabels(header);
    QFont font = table_->horizontalHeader()->font();
    font.setBold(true);
    table_->horizontalHeader()->setFont(font);

    table_->resizeColumnToContents(2);

    table_->setColumnWidth(1, 800);

    table_->verticalHeader()->setDefaultSectionSize(80); //设置行高
    
    table_->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table_->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table_->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);


    createWidget00(0);
    createWidget01(1);
    createWidget02(2);
    createWidget03(3);
    createWidget04(4);
    createWidget05(5);
    createWidget06(6);
    createWidget07(7);
    createWidget08(8);
    createWidget09(9);
    createWidget10(10);
    createWidget11(11);
    createWidget12(12);
    createWidget13(13);
    createWidget14(14);
    createWidget15(15);
    createWidget16(16);
    createWidget17(17);
    createWidget18(18);
    createWidget19(19);
    createWidget20(20);
    createWidget21(21);
    createWidget22(22);
    createWidget23(23);
    createWidget24(24);
    createWidget25(25);
    createWidget26(26);
    createWidget27(27);

    layout->addWidget(table_);

    this->setLayout(layout);

    resize(1200, 700);

    //watch_dir();
}

MainWindow::~MainWindow()
{
    disconnect(thread_, SIGNAL(started()), worker_, SLOT(doWork()));
    disconnect(thread_, SIGNAL(finished()), worker_, SLOT(deleteLater()));

    if (thread_) {
        if (thread_->isRunning()) {
            thread_->quit();
            thread_->wait();
        }
        delete thread_;
        thread_ = NULL;
    }

    if (worker_) {
        delete worker_;
        worker_ = NULL;
    }

    //delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::onChange(const QString& filename)
{
    qDebug() << filename;
    setQssStyle(filename);
}

void MainWindow::watch_dir()
{
    

    
}

void MainWindow::createWidget00(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QPushButton"));
    //table_->setItem(row, 1, new QTableWidgetItem("test"));


    QWidget* pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    QHBoxLayout* layout = new QHBoxLayout;

    auto button1 = new QPushButton(tr("删除"));
    button1->setProperty("class", "delete");
    button1->setFixedWidth(100);   

    auto button2 = new QPushButton(tr("禁用"));
    button2->setEnabled(false);

    auto button3 = new QPushButton;
    button3->setObjectName("button3");
    button3->setCheckable(true);

    layout->addWidget(button1);   
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);

}

void MainWindow::createWidget01(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QLabel"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    auto label = new QLabel(tr("删除"));    
    label->setFixedWidth(100);
    layout->addWidget(label);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget02(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QCheckBox"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;
    auto checkbox1 = new QCheckBox(tr("test1"));
    auto checkbox2 = new QCheckBox(tr("test2"));
    auto checkbox3 = new QCheckBox(tr("test3"));
    
    layout->addWidget(checkbox1);
    layout->addWidget(checkbox2);
    layout->addWidget(checkbox3);
    
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 200);
}

void MainWindow::createWidget03(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QRadioButton"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;
    auto radio1 = new QRadioButton(tr("test1"));
    auto radio2 = new QRadioButton(tr("test2"));   
    auto radio3 = new QRadioButton(tr("test3"));
    layout->addWidget(radio1);
    layout->addWidget(radio2);
    layout->addWidget(radio3);
    
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 200);
}

void MainWindow::createWidget04(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QComboBox"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    auto combobox = new QComboBox;
    combobox->addItem(tr("test"));
    layout->addWidget(combobox);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget05(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QSpinBox QDoubleSpinBox"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto spinbox = new QSpinBox();
    spinbox->setFixedWidth(100);

    auto double_spinbox = new QDoubleSpinBox();
    double_spinbox->setFixedWidth(100);  

    layout->addWidget(spinbox);
    layout->addWidget(double_spinbox);   

    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget06(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QGroupBox"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    auto groupbox = new QGroupBox();
    groupbox->setTitle("test");
    groupbox->setFixedWidth(200);
    layout->addWidget(groupbox);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget07(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QLineEdit"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    auto edit = new QLineEdit();
    edit->setFixedWidth(200);
    layout->addWidget(edit);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget08(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QToolButton"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    auto toolbutton = new QToolButton();    
    layout->addWidget(toolbutton);
    layout->addStretch();
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget09(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QTreeWidget"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;
    


    auto tree = new QTreeWidget;
    tree->setObjectName("tree");
    tree->setHeaderHidden(true);
    auto root = new QTreeWidgetItem(tree);
    root->setText(0, tr("策略参数"));

    for (int i = 0; i < 10; ++i) {
        auto item = new QTreeWidgetItem(root);
        auto item_layout = new QGridLayout;
        QWidget* pWidget = new QWidget;

        auto label = new QLabel(QString("参数%1").arg(i), pWidget);
        label->setProperty("is_arg", true);
        auto pDobleSpinBox = new QDoubleSpinBox(pWidget);
        pDobleSpinBox->setValue(10);
        item_layout->addWidget(label, 0, 0, 1, 1, Qt::AlignLeft);
        item_layout->addWidget(pDobleSpinBox, 0, 1, 1, 1, Qt::AlignLeft);
        item_layout->setColumnStretch(0, 1);
        item_layout->setColumnStretch(1, 5);
        pWidget->setLayout(item_layout);
        tree->setItemWidget(item, 0, pWidget);
    }


    auto root2 = new QTreeWidgetItem(tree);
    root2->setText(0, tr("数字货币现货交易类库"));

    for (int i = 0; i < 15; ++i) {
        auto item = new QTreeWidgetItem(root2);
        auto item_layout = new QGridLayout;
        QWidget* pWidget = new QWidget;

        auto label = new QLabel(QString("参数%1").arg(i), pWidget);
        label->setProperty("is_arg", true);
        auto pDobleSpinBox = new QDoubleSpinBox(pWidget);
        pDobleSpinBox->setValue(10);
        item_layout->addWidget(label, 0, 0, 1, 1, Qt::AlignLeft);
        item_layout->addWidget(pDobleSpinBox, 0, 1, 1, 1, Qt::AlignLeft);
        item_layout->setColumnStretch(0, 1);
        item_layout->setColumnStretch(1, 5);
        pWidget->setLayout(item_layout);
        tree->setItemWidget(item, 0, pWidget);
    }

    tree->addTopLevelItem(root);
    tree->addTopLevelItem(root2);

    tree->expandAll();



    layout->addWidget(tree);    
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 500);
}

void MainWindow::createWidget10(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QListView"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;
    
    auto listview = new QListView;

    QStringListModel* slm = new QStringListModel(this);
    QStringList* sl = new QStringList();
    sl->append("asdfsadfsa");
    sl->append("asdfsadfsa");
    sl->append("asdfsadfsa");
    slm->setStringList(*sl);
    listview->setModel(slm);
    delete sl;


    layout->addWidget(listview);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 500);
}

void MainWindow::createWidget11(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QListWidget"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto listWidget = new QListWidget;

    for (int i = 0; i < 10; ++i) {
        QStringList list;
        list << QString(tr("设备_%1")).arg(i);
        listWidget->addItems(list);
    }
    


    layout->addWidget(listWidget);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 500);
}

void MainWindow::createWidget12(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QProgressBar"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto progressbar = new QProgressBar;
    progressbar->setValue(80);

    layout->addWidget(progressbar);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    
}

void MainWindow::createWidget13(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QTextEdit"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto textedit = new QTextEdit;
    textedit->setText("test");

    layout->addWidget(textedit);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget14(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QSlider"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto slider = new QSlider;    
    slider->setOrientation(Qt::Horizontal);
    slider->setValue(80);

    layout->addWidget(slider);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget15(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QTabWidget"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto tabWidget = new QTabWidget;
    auto label1 = new QLabel;
    auto label2 = new QLabel;
    auto label3 = new QLabel;

    tabWidget->addTab(label1, tr("test1"));
    tabWidget->addTab(label2, tr("test2"));
    tabWidget->addTab(label3, tr("test3"));
    
    layout->addWidget(tabWidget);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 200);
}

void MainWindow::createWidget16(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QTableWidget"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto tableWidget = new QTableWidget(5, 3);
    tableWidget->setFocusPolicy(Qt::NoFocus);

    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->horizontalHeader()->setFixedHeight(50); //设置表头的高度

    QStringList header;
    header << tr("名称") << tr("交易对") << tr("操作项");
   
    tableWidget->setHorizontalHeaderLabels(header);
    QFont font = table_->horizontalHeader()->font();
    font.setBold(true);
    tableWidget->horizontalHeader()->setFont(font);

    tableWidget->verticalHeader()->setDefaultSectionSize(80); //设置行高

    tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);


    layout->addWidget(tableWidget);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 200);
}

void MainWindow::createWidget17(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QFrame"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto frame = new QFrame;   
    frame->setFixedSize(200, 100);
    

    layout->addWidget(frame);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    table_->setRowHeight(row, 200);
}

void MainWindow::createWidget18(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QAbstractButton"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto button1 = new QPushButton;    


    layout->addWidget(button1);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
    
}

void MainWindow::createWidget19(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QTimeEdit"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto timeEdit = new QTimeEdit;
    auto timeEdit2 = new QTimeEdit;
    timeEdit2->setCalendarPopup(true);

    layout->addWidget(timeEdit);
    layout->addWidget(timeEdit2);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);

}

void MainWindow::createWidget20(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QDateEdit"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto dateEdit = new QDateEdit;

    auto dateEdit2 = new QDateEdit;
    dateEdit2->setCalendarPopup(true);


    layout->addWidget(dateEdit);
    layout->addWidget(dateEdit2);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget21(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QDateTimeEdit"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto datetimeEdit = new QDateTimeEdit;
    auto datetimeEdit2 = new QDateTimeEdit;
    datetimeEdit2->setCalendarPopup(true);

    layout->addWidget(datetimeEdit);
    layout->addWidget(datetimeEdit2);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget22(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QToolBar"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto toolbar = new QToolBar;
   

    layout->addWidget(toolbar);   
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget23(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QStatusBar"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QVBoxLayout;

    auto statusbar = new QStatusBar;


    layout->addWidget(statusbar);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget24(int row)
{
    table_->setItem(row, 0, new QTableWidgetItem("QMenuBar"));

    auto pWidget = new QWidget;
    pWidget->setObjectName(QString("row_%1").arg(row));
    auto layout = new QHBoxLayout;

    auto menubar = new QMenuBar;

    QMenu* menu[10];
    QAction* act[10];

    menu[0] = new QMenu("文件");
    menu[0]->addAction("编辑");
    menu[0]->addAction("查看");
    menu[0]->addAction("工具");

    act[0] = new QAction("新建", this);
    act[0]->setShortcut(Qt::CTRL | Qt::Key_A);
    act[0]->setStatusTip("这是一个新建菜单");

    act[1] = new QAction("打开", this);
    act[1]->setCheckable(true);

    menu[1] = new QMenu("保存");
    menu[1]->addAction(act[0]);
    menu[1]->addAction(act[1]);

    menu[2] = new QMenu("打印");
    menu[2]->addAction("打印设置");
    menu[2]->addMenu(menu[1]);

    
    menubar->addMenu(menu[0]);
    menubar->addMenu(menu[2]);


    layout->addWidget(menubar);
    pWidget->setLayout(layout);
    table_->setCellWidget(row, 1, pWidget);
}

void MainWindow::createWidget25(int row)
{

}

void MainWindow::createWidget26(int row)
{

}

void MainWindow::createWidget27(int row)
{

}

