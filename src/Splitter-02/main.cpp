#include <QApplication>
#include <QSplitter>
#include <QGridLayout>
#include <QComboBox>
#include <QScrollArea>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSplitter>
#include <QFormLayout>

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


    QWidget w;
    w.setMinimumSize(800, 600);
    w.setStyleSheet("QSplitter::handle {background-color: green;}");


    QVBoxLayout* layout = new QVBoxLayout;

    QSplitter* splitterMain = new QSplitter(Qt::Vertical, 0);


    QWidget* topWidget = new QWidget(splitterMain);
    QWidget* bottomWidget = new QWidget(splitterMain);

    QGridLayout* topLayout = new QGridLayout;
    QGridLayout* bottomLayout = new QGridLayout;



    QLabel* label0 = new QLabel("label0");
    QLineEdit* edit0 = new QLineEdit;

    QLabel* label1 = new QLabel("label1");
    label1->setAlignment(Qt::AlignTop);
    QScrollArea* scrollArea1 = createScrollArea();


    topLayout->addWidget(label0, 0, 0, 1, 1, Qt::AlignRight);
    topLayout->addWidget(edit0, 0, 1, 1, 1);

    topLayout->addWidget(label1, 1, 0, 1, 1, Qt::AlignRight);
    topLayout->addWidget(scrollArea1, 1, 1, 1, 1);



    QLabel* label2 = new QLabel("label2");
    label2->setAlignment(Qt::AlignTop);
    QScrollArea* scrollArea2 = createScrollArea();

    QPushButton* button1 = new QPushButton("click me!");
    button1->setFixedWidth(200);




    bottomLayout->addWidget(label2, 0, 0, 1, 1, Qt::AlignRight);
    bottomLayout->addWidget(scrollArea2, 0, 1, 1, 1);

    bottomLayout->addWidget(button1, 1, 1, 1, 1);


    topWidget->setLayout(topLayout);
    bottomWidget->setLayout(bottomLayout);


    // 设置缩放因子
    splitterMain->setStretchFactor(0,7);
    splitterMain->setStretchFactor(1,3);



    layout->addWidget(splitterMain);
    layout->setMargin(0);

    w.setLayout(layout);

    w.show();

    return a.exec();
}
