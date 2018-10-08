#include "CloseButton.h"
#include "TabBarHelper.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

MYCloseButton::MYCloseButton(QWidget* parent)
    : QAbstractButton(parent)
{
    setObjectName("combotabbar_tabs_close_button");
    setFocusPolicy(Qt::NoFocus);
    setCursor(Qt::ArrowCursor);
    resize(sizeHint());
}

QSize MYCloseButton::sizeHint() const
{
    ensurePolished();
    int width = style()->pixelMetric(QStyle::PM_TabCloseIndicatorWidth, nullptr, this);
    int height = style()->pixelMetric(QStyle::PM_TabCloseIndicatorHeight, nullptr, this);
    return QSize(width, height);
}

void MYCloseButton::enterEvent(QEvent* event)
{
    if (isEnabled()) {
        update();
    }

    QAbstractButton::enterEvent(event);
}

void MYCloseButton::leaveEvent(QEvent* event)
{
    if (isEnabled()) {
        update();
    }

    QAbstractButton::leaveEvent(event);
}

void MYCloseButton::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    opt.state |= QStyle::State_AutoRaise;

    // update raised state on scrolling
    bool isUnderMouse = rect().contains(mapFromGlobal(QCursor::pos()));

    if (isEnabled() && isUnderMouse && !isChecked() && !isDown()) {
        opt.state |= QStyle::State_Raised;
    }
    if (isChecked()) {
        opt.state |= QStyle::State_On;
    }
    if (isDown()) {
        opt.state |= QStyle::State_Sunken;
    }

    if (TabBarHelper* tb = qobject_cast<TabBarHelper*>(parent())) {
        int index = tb->currentIndex();
        QTabBar::ButtonPosition closeSide = (QTabBar::ButtonPosition)style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, 0, tb);
        if (tb->tabButton(index, closeSide) == this && tb->isActiveTabBar()) {
            opt.state |= QStyle::State_Selected;
        }
    }

    style()->drawPrimitive(QStyle::PE_IndicatorTabClose, &opt, &p, this);
}