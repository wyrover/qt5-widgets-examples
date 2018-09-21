#include "info_widget.h"
#include "ui_info_widget.h"

#include <QPainter>
#include <QStyleOption>


InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
