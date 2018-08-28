#include "taglabel.h"

#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVariant>

TagLabel::TagLabel(const QString &text, const QString& bkcolor, const QString& icon_filename, QWidget *parent)
    : text_(text), bkcolor_(bkcolor), icon_filename_(icon_filename), QWidget(parent)
{
    setupUI();
}

TagLabel::TagLabel(QWidget *parent) :
    QWidget(parent)
{


    setupUI();

}

TagLabel::~TagLabel()
{

}

void TagLabel::setupUI()
{
	this->setAttribute(Qt::WA_StyledBackground);

    label_ = new QLabel(this);
	label_->setAlignment(Qt::AlignCenter);
	
    updateUI();
	
    close_button_ = new QPushButton(QIcon(icon_filename_), "", this);
    close_button_->setProperty("StatusBtn", QVariant(true));
    close_button_->setToolTip(tr("Remove"));
    close_button_->setFocusPolicy(Qt::NoFocus);
    close_button_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //close_button_->hide();

	connect(close_button_, &QPushButton::clicked,
		this, [this]() {
		emit removalRequested(text_);
	});

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label_);
    layout->addWidget(close_button_);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    setLayout(layout);

	QStringList qss;
	qss.append(QString("TagLabel { background-color: %1; color: #ffffff; border-radius:5px; }")
		.arg(bkcolor_));
	qss.append(QString("TagLabel QLabel { color: #ffffff; font-weight: 500; }"));
	qss.append(QString("TagLabel QPushButton { background-color:%1; border-style: solid; border-radius:5px; }").arg(bkcolor_));

	this->setStyleSheet(qss.join(""));
}

void TagLabel::updateUI()
{
    label_->setText(text_);
    label_->setToolTip(text_);
}


void TagLabel::setText(const QString& text)
{
	text_ = text;
	updateUI();
}