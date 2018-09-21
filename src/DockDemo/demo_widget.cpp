#include "demo_widget.h"
#include "ui_demo_widget.h"

DemoWidget::DemoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DemoWidget)
{
    ui->setupUi(this);
}

DemoWidget::~DemoWidget()
{
    delete ui;
}
