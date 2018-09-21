#include "CToastLabel.h"

#include <QPainter>
#include <QPropertyAnimation>

CToastLabel::CToastLabel(QWidget *parent)
    : QLabel(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_QuitOnClose);
    setAttribute(Qt::WA_DeleteOnClose);
    m_font = font();
    this->setFontSize(0X10); // 默认字体 16 号
    this->setFontMargin(20, 20); // 设置边缘

    this->setMaximumWidth(600);
    this->setAlignment(Qt::AlignTop);
    this->adjustSize();
    this->setWordWrap(true);

    connect(&m_timer, SIGNAL(timeout()), SLOT(closeAnimation()));
    m_timer.setInterval(1500);
    m_timer.start();
}

CToastLabel::CToastLabel(const QString &text, QWidget *parent)
    : CToastLabel(parent)
{
    setText(text);
}

CToastLabel::~CToastLabel()
{
    m_timer.stop();
}

// 设置边缘
void CToastLabel::setFontMargin(int height, int width)
{
    m_margin.setX(height);
    m_margin.setY(width);
}

void CToastLabel::setTimerInterval(int msecond)
{
    m_timer.stop();
    m_timer.setInterval(msecond);
    m_timer.start();
}

int CToastLabel::getTimerInterval() const
{
    return m_timer.interval();
}

void CToastLabel::setFontSize(int size)
{
    m_font.setPointSize(size);
    setFont(m_font);
}

int CToastLabel::getFontSize() const
{
    return m_font.pointSize();
}

void CToastLabel::setBold(bool bold)
{
    m_font.setBold(bold);
    setFont(m_font);
}

bool CToastLabel::bold() const
{
    return m_font.bold();
}

void CToastLabel::popup(QWidget *parent)
{
    QPoint globalPoint = parent->mapToGlobal(QPoint(0, 0));
    move(globalPoint.x() + (parent->width() - width()) / 2,
         globalPoint.y() + (parent->height() - height()) / 2);
    show();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void CToastLabel::setText(const QString &text)
{
    QFontMetrics metrics = QFontMetrics(m_font);
    setFixedSize(metrics.width(text) + m_margin.x(), metrics.height() + m_margin.y());
    QLabel::setText(text);
}

void CToastLabel::closeAnimation()
{
    m_timer.stop();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity", this);
    animation->setDuration(1000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), SLOT(close()));
}

//void CToastLabel::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor(150, 150, 150, 175));
//    painter.drawRoundRect(rect(), 6, 6);
//    painter.setPen(QColor(255, 255, 255));
//    painter.drawText(rect(), Qt::AlignCenter, text());
//    painter.end();
//}