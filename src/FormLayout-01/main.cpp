#include "widget.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTreeWidget>
#include <QListWidget>
#include <QFormLayout>
#include <QScrollArea>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QComboBox>
#include <QGroupBox>

QScrollArea* scroll_area_;
QWidget* scroll_widget_;
QVBoxLayout* scroll_area_layout_;

QWidget* createItem(int i)
{
    QWidget* item = scroll_area_->findChild<QWidget*>(QString("#item_%1").arg(i));

    if (!item) {
        QWidget* pWidget = new QWidget(scroll_widget_);
        pWidget->setObjectName(QString("#item_%1").arg(i));
        /*pWidget->setStyleSheet("QWidget"
            "{background:red;}");*/

        QHBoxLayout* itemLayout = new QHBoxLayout();

        QCheckBox* pCheckBox = new QCheckBox(pWidget);
        pCheckBox->setObjectName(QString("#item_chk_%1").arg(i));
        pCheckBox->setChecked(true);
        pCheckBox->setVisible(false);

        QLabel* pLabel = new QLabel(QString("#%1").arg(i), pWidget);
        QDoubleSpinBox* pDobleSpinBox = new QDoubleSpinBox(pWidget);
        pDobleSpinBox->setProperty("tag", i);

        QLineEdit* pEdit = new QLineEdit(QString("#%1").arg(i), pWidget);

        if (i % 2 == 0) {
            pEdit->setEchoMode(QLineEdit::Password);
            qDebug() << "6666";
        } else {
            qDebug() << "7777";
        }

        QComboBox* pComboBox = new QComboBox(pWidget);
        pComboBox->addItem("111", "111");
        pComboBox->addItem("222", "222");
        pComboBox->addItem("333", "333");


        QPushButton* pButton = new QPushButton(QString("button %1").arg(i), pWidget);
        if (pButton) {
            pButton->setObjectName(QString("#%1").arg(i));
            pButton->setMinimumSize(pButton->size());

//            connect(pButton, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
//            connect(pDobleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_spin_valueChanged(double)));
//            connect(pCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_item_checkBox_toggled(bool)));

            itemLayout->addWidget(pCheckBox);
            itemLayout->addWidget(pLabel);
            itemLayout->addWidget(pDobleSpinBox);
            itemLayout->addWidget(pEdit);
            itemLayout->addWidget(pComboBox);
            itemLayout->addWidget(pButton);

            pWidget->setLayout(itemLayout);


            return pWidget;

        }

    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    QWidget *window = new QWidget;
    QPushButton *button1 = new QPushButton("One11111111111111111111111");
    QLineEdit *lineEdit1 = new QLineEdit();
    QPushButton *button2 = new QPushButton("Two");
    QLineEdit *lineEdit2 = new QLineEdit();
    QPushButton *button3 = new QPushButton("Three");
    QLineEdit *lineEdit3 = new QLineEdit();
    QLabel* label4 = new QLabel("test");

    QTreeWidget* tree1 = new QTreeWidget();
    QListWidget* list1 = new QListWidget();
    QListWidget* list2 = new QListWidget();

    QGroupBox* groupbox = new QGroupBox();
    groupbox->setTitle(QString("参数"));

    QScrollArea* scroll_area_ = new QScrollArea();
    scroll_widget_ = new QWidget;
    scroll_area_layout_ = new QVBoxLayout(scroll_widget_);
    scroll_area_layout_->setSizeConstraint(QVBoxLayout::SetMinAndMaxSize);
    scroll_area_layout_->setAlignment(Qt::AlignTop);
    scroll_widget_->setLayout(scroll_area_layout_);

    scroll_area_->setWidget(scroll_widget_);
    scroll_area_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    scroll_area_->setWidgetResizable(true);

    QVBoxLayout* groupbox_layout = new QVBoxLayout;
    groupbox_layout->addWidget(scroll_area_);
    groupbox->setLayout(groupbox_layout);

    for (int i = 1; i <= 10; ++i) {
        QWidget* itemWidget = createItem(i);
        if (itemWidget)
            scroll_widget_->layout()->addWidget(itemWidget);
    }

    QFormLayout *layout = new QFormLayout;
    layout->addRow(button1, lineEdit1);
    layout->addRow(button2, lineEdit2);
    layout->addRow(button3, lineEdit3);
    layout->addRow(label4, list2);
    layout->addRow("scroll", groupbox);


    layout->addRow(tree1);
    layout->addRow("1111", list1);
    layout->setSpacing(10);
    layout->setMargin(10);
    layout->setLabelAlignment(Qt::AlignRight);

    window->setLayout(layout);
    window->show();

    return a.exec();
}
