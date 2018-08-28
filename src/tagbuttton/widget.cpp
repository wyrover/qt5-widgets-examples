#include "widget.h"
#include "ui_widget.h"
#include "taglabel.h"

#include <QHBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)

{


    QHBoxLayout* layout = new QHBoxLayout;

	

    TagLabel* tag0 = new TagLabel("BotVS / BTC_USD", "#d9534f", ":/resources/assets/close.svg");
	tag0->setFixedSize(200, 30);

	connect(tag0, &TagLabel::removalRequested, [=](const QString& text) {
		qDebug() << text;
	});

	TagLabel* tag1 = new TagLabel("BotVS / ETH_BTC", "#5bc0de", ":/resources/assets/close.svg");
	tag1->setFixedSize(200, 30);

	connect(tag1, &TagLabel::removalRequested, [=](const QString& text) {
		qDebug() << text;
	});
	
    layout->addWidget(tag0);
	layout->addWidget(tag1);

    setLayout(layout);
}

Widget::~Widget()
{

}
