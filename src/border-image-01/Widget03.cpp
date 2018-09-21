#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget03.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QDebug>

class CustomSpinBox : public QDoubleSpinBox
{
public:
    explicit CustomSpinBox(QWidget *parent = Q_NULLPTR);
    ~CustomSpinBox();
public:    
    virtual QString textFromValue(double val) const override;

public Q_SLOTS:
    void setValue(double val);
};

CustomSpinBox::CustomSpinBox(QWidget *parent /*= Q_NULLPTR*/)
{
    this->setMinimum(std::numeric_limits<double>::lowest());
    this->setMaximum(std::numeric_limits<double>::max());
    this->setDecimals(8);
}

CustomSpinBox::~CustomSpinBox()
{

}

QString CustomSpinBox::textFromValue(double val) const
{

    QString tmp = QString::number(val, 'f', 8).remove(QRegularExpression("0+$"));
    tmp = tmp.remove(QRegularExpression("\\.$"));
    return tmp;
}

void CustomSpinBox::setValue(double val)
{
    

    QString tmp = QString::number(val, 'f', 8).remove(QRegularExpression("0+$"));

    //QString tmp(QString("%1").arg(val));    
    //qDebug() << tmp;

    if (tmp.indexOf(".") > 0) {
        int bit_length = tmp.length() - (tmp.indexOf(".") + 1);       
        if (bit_length == 1) {
            this->setSingleStep(0.1);
        } else if (bit_length == 2) {
            this->setSingleStep(0.01);
        } else if (bit_length == 3) {
            this->setSingleStep(0.001);
        } else if (bit_length == 4) {
            this->setSingleStep(0.0001);
        } else if (bit_length == 5) {
            this->setSingleStep(0.00001);
        } else if (bit_length == 6) {
            this->setSingleStep(0.000001);
        } else if (bit_length == 7) {
            this->setSingleStep(0.0000001);
        } else if (bit_length == 8) {
            this->setSingleStep(0.00000001);
        }
    } else {
        this->setSingleStep(1);
        
    }

    

    __super::setValue(tmp.toDouble());
}

Widget03::Widget03(QWidget *parent)
    : QWidget(parent)
{
  
    auto layout = new QVBoxLayout;

    auto spinBox = new CustomSpinBox();
    spinBox->setObjectName("spinBox");



    double aaaa = 2.00000001;

    spinBox->setValue(aaaa);

    layout->addWidget(spinBox);
  
    setLayout(layout);


    this->setMinimumSize(800, 600);
}

Widget03::~Widget03()
{
   

}