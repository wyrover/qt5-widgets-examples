#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

QScrollArea* createScrollArea()
{
    QStringList keys;
    QList<int> status;
    for(int i=0; i< 10; i++){
        keys << QString("key %1").arg(i);
        status << i%4;
    }


    QScrollArea *scroll = new QScrollArea;
    QWidget *content_widget = new QWidget;
    QFormLayout *formLayout = new QFormLayout(content_widget);


    QStringList items{"Present", "Present and Voting", "Absent", "Absent from Commitee"};

    for(int x=0; x < keys.size(); x++)
    {

        QComboBox *combo = new QComboBox;
        combo->addItems(items);
        combo->setProperty("MyIndex", x);
        combo->setCurrentIndex(status[x]);
        formLayout->addRow(keys.at(x),combo);
        //connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(roll(int)));
    }

    QLayoutItem* layoutItem = formLayout->takeAt(0);
    layoutItem->widget()->setVisible(false);
    layoutItem = formLayout->takeAt(1);
    layoutItem->widget()->setVisible(false);


    scroll->setWidget(content_widget);
    return scroll;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QStringList keys;
    QList<int> status;
    for(int i=0; i< 100; i++){
        keys << QString("key %1").arg(i);
        status << i%4;
    }

    QWidget *wdg = new QWidget;
    wdg->setMinimumSize(800, 600);

    //QFormLayout* layout = new QFormLayout;

    QGridLayout* layout = new QGridLayout;

//    for (int i = 0; i < 50; ++i) {
//        QLabel* pLabel = new QLabel("test1111111111111111111111111111111111111111111111111");
//        QLabel* pLabel2 = new QLabel("test11111111");

//        layout->addWidget(pLabel, i, 0, 1, 1);
//        layout->addWidget(pLabel2, i, 1, 1, 1);

//    }


    QLabel* Label0 = new QLabel("参数");
    QLineEdit* edit0 = new QLineEdit("标题11111111111");

    layout->addWidget(Label0, 0, 0, 1, 1);
    layout->addWidget(edit0, 0, 1, 1, 1);


    QLabel* Label1 = new QLabel("参数");
    Label1->setAlignment(Qt::AlignTop);
    QGroupBox* group = new QGroupBox("test");

    QVBoxLayout* group_layout = new QVBoxLayout;
    group->setLayout(group_layout);

    layout->addWidget(Label1, 1, 0, 1, 1);
    layout->addWidget(group, 1, 1, 1, 1);

    QLabel* Label2 = new QLabel("参数参数");
    Label2->setAlignment(Qt::AlignTop);

    QComboBox* combox1 = new QComboBox;



    layout->addWidget(Label2, 2, 0, 1, 1);
    layout->addWidget(combox1, 2, 1, 1, 1);


    QPushButton* button1 = new QPushButton("点我");
    button1->setFixedWidth(200);
    layout->addWidget(button1, 3, 1, 1, 1);



    layout->setRowStretch(1, 900000);
    //layout->setAlignment(Qt::AlignTop);
    layout->setColumnStretch(1, 900000);

    group_layout->addWidget(createScrollArea(), 4);
    group_layout->addWidget(createScrollArea(), 1);

//    for (int j = 0; j < 50; ++j) {
//         QLabel* pLabel = new QLabel("test1111111111111111111111111111111111111111111111111");
//         group_layout->addWidget(pLabel);
//    }


//    QGroupBox* group = new QGroupBox("test");

//    layout1->addWidget(group);
////    group->setMinimumHeight(600);
////    group->setMaximumHeight(2000);

//    //layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

//    layout->addLayout(layout1);



    wdg->setLayout(layout);
    wdg->show();

//    QWidget *wdg = new QWidget;
//    QScrollArea *scroll = new QScrollArea;

//    QWidget *content_widget = new QWidget;

//    QFormLayout *formLayout = new QFormLayout(content_widget);


//    QStringList items{"Present", "Present and Voting", "Absent", "Absent from Commitee"};

//    for(int x=0; x < keys.size(); x++)
//    {

//        QComboBox *combo = new QComboBox;
//        combo->addItems(items);
//        combo->setProperty("MyIndex", x);
//        combo->setCurrentIndex(status[x]);
//        formLayout->addRow(keys.at(x),combo);
//        //connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(roll(int)));
//    }

//    scroll->setWidget(content_widget);
//    wdg->setLayout(new QVBoxLayout);
//    wdg->layout()->addWidget(scroll);
//    wdg->show();

    return a.exec();
}
