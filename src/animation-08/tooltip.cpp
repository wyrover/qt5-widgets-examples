#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif

#include "tooltip.h"
#include <QVBoxLayout>
#include <QToolButton>
#include <QVariant>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QLabel>


ToolTip::ToolTip(QWidget *parent /*= 0*/)
    : QWidget(parent)
{

    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setContentsMargins(0, 0, 0, 0);

    auto layout = new QVBoxLayout;

    info_ = new QLabel;
    info_->setObjectName("info");
    info_->setMaximumWidth(660);
    info_->setAlignment(Qt::AlignTop);
    info_->adjustSize();
    info_->setWordWrap(true);

    layout->addWidget(info_);
    layout->addStretch();
    setLayout(layout);
    
}

ToolTip::~ToolTip()
{

}

void ToolTip::setText(const QString& text)
{
    info_->setText(text);
    
}
