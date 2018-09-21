#include "tipwidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

TipWidget::TipWidget(const QString &text, QWidget *parent) : QFrame(parent)//: QWidget(parent, Qt::SubWindow)
{
    setWindowFlags(windowFlags() | Qt::SubWindow);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    //    setTransparent(true);

    setWindowFlags(/*Qt::ToolTip | */Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setContentsMargins(0, 0, 0, 0);
    setObjectName("TipWidget");//kobe: 设置背景色

    m_radius = 4;
    w_shadow = 20;
    shadow_margins = QMargins(20, 20, 20, 20);
    m_borderColor = QColor(0, 0, 0, 0.2 * 255);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);


    text_label = new QLabel(text);
    text_label->adjustSize();
    text_label->setStyleSheet("QLabel{font-size: 16px;color: #ffffff;}");
    text_label->setAlignment(Qt::AlignCenter);

    layout->addStretch();
    layout->addWidget(text_label);
    layout->addStretch();
    this->setLayout(layout);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    hide();
}

TipWidget::~TipWidget()
{

}

void TipWidget::setTransparent(bool transparent)
{
    if (transparent) {
        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
        set_widget_opacity(0.5);
    } else {
        setAttribute(Qt::WA_TranslucentBackground, false);
        setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint);
    }
}

void TipWidget::set_widget_opacity(const float &opacity)
{
    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
    this->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(opacity);
}

void TipWidget::setText(const QString text)
{
    this->text_label->setText(text);
}

QBrush TipWidget::background() const
{
    return this->m_background;
}

int TipWidget::radius() const
{
    return this->m_radius;
}

QColor TipWidget::borderColor() const
{
    return this->m_borderColor;
}

void TipWidget::setBackground(QBrush background)
{
    this->m_background = background;
}

void TipWidget::setRadius(int radius)
{
    this->m_radius = radius;
}

void TipWidget::setBorderColor(QColor borderColor)
{
    this->m_borderColor = borderColor;
}

void TipWidget::aniFinished()
{
    this->hide();
}