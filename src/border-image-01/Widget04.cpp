#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget04.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>


Widget04::Widget04(QWidget *parent)
    : QWidget(parent)
{
  
    this->setObjectName("widget04");
    auto layout = new QVBoxLayout;

    auto combobox1 = new QComboBox;
    combobox1->setObjectName("combobox1");
    combobox1->setToolTip(tr("combobox1"));
    combobox1->setEditable(true);

    

    layout->addWidget(combobox1);
   
    setLayout(layout);


    this->setMinimumSize(800, 600);
}

Widget04::~Widget04()
{
   

}