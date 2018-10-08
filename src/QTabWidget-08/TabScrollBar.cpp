#include "TabScrollBar.h"
#include "TabBarHelper.h"
#include <toolbutton.h>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QStyle>
#include <QStyleOption>
#include <QApplication>
#include <QWheelEvent>
#include <QPainter>


TabScrollBar::TabScrollBar(QWidget* parent)
    : QScrollBar(Qt::Horizontal, parent)
{
    m_animation = new QPropertyAnimation(this, "value", this);
}

TabScrollBar::~TabScrollBar()
{
}

bool TabScrollBar::isScrolling() const
{
    return m_animation->state() == QPropertyAnimation::Running;
}

void TabScrollBar::animateToValue(int to, QEasingCurve::Type type)
{
    to = qBound(minimum(), to, maximum());
    int lenght = qAbs(to - value());
    int duration = qMin(1500, 200 + lenght / 2);

    m_animation->stop();
    m_animation->setEasingCurve(type);
    m_animation->setDuration(duration);
    m_animation->setStartValue(value());
    m_animation->setEndValue(to);
    m_animation->start();
}


TabBarScrollWidget::TabBarScrollWidget(QTabBar* tabBar, QWidget* parent)
    : QWidget(parent)
    , m_tabBar(tabBar)
    , m_usesScrollButtons(false)
    , m_totalDeltas(0)
{
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setFocusPolicy(Qt::NoFocus);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_scrollBar = new TabScrollBar(m_scrollArea);
    m_scrollArea->setHorizontalScrollBar(m_scrollBar);
    m_scrollArea->setWidget(m_tabBar);

    m_leftScrollButton = new ToolButton(this);
    m_leftScrollButton->setFocusPolicy(Qt::NoFocus);
    m_leftScrollButton->setAutoRaise(true);
    m_leftScrollButton->setObjectName("tabbar-button-left");
    m_leftScrollButton->setAutoRepeat(true);
    m_leftScrollButton->setAutoRepeatDelay(200);
    m_leftScrollButton->setAutoRepeatInterval(200);
    connect(m_leftScrollButton, SIGNAL(pressed()), this, SLOT(scrollStart()));
    connect(m_leftScrollButton, SIGNAL(doubleClicked()), this, SLOT(scrollToLeftEdge()));
    connect(m_leftScrollButton, SIGNAL(middleMouseClicked()), this, SLOT(ensureVisible()));

    m_rightScrollButton = new ToolButton(this);
    m_rightScrollButton->setFocusPolicy(Qt::NoFocus);
    m_rightScrollButton->setAutoRaise(true);
    m_rightScrollButton->setObjectName("tabbar-button-right");
    m_rightScrollButton->setAutoRepeat(true);
    m_rightScrollButton->setAutoRepeatDelay(200);
    m_rightScrollButton->setAutoRepeatInterval(200);
    connect(m_rightScrollButton, SIGNAL(pressed()), this, SLOT(scrollStart()));
    connect(m_rightScrollButton, SIGNAL(doubleClicked()), this, SLOT(scrollToRightEdge()));
    connect(m_rightScrollButton, SIGNAL(middleMouseClicked()), this, SLOT(ensureVisible()));

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(m_leftScrollButton);
    hLayout->addWidget(m_scrollArea);
    hLayout->addWidget(m_rightScrollButton);
    setLayout(hLayout);

    m_scrollArea->viewport()->setAutoFillBackground(false);
    connect(m_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateScrollButtonsState()));

    updateScrollButtonsState();
    overFlowChanged(false);
}

QTabBar* TabBarScrollWidget::tabBar()
{
    return m_tabBar;
}

QScrollArea* TabBarScrollWidget::scrollArea()
{
    return m_scrollArea;
}

TabScrollBar* TabBarScrollWidget::scrollBar()
{
    return m_scrollBar;
}

void TabBarScrollWidget::ensureVisible(int index, int xmargin)
{
    if (index == -1) {
        index = m_tabBar->currentIndex();
    }

    if (index < 0 || index >= m_tabBar->count()) {
        return;
    }
    xmargin = qMin(xmargin, m_scrollArea->viewport()->width() / 2);

    // Qt Bug? the following lines were taken from QScrollArea::ensureVisible() and
    // then were fixed. The original version caculates wrong values in RTL layouts.
    const QRect logicalTabRect = QStyle::visualRect(m_tabBar->layoutDirection(), m_tabBar->rect(), m_tabBar->tabRect(index));
    int logicalX = QStyle::visualPos(Qt::LeftToRight, m_scrollArea->viewport()->rect(), logicalTabRect.center()).x();

    if (logicalX - xmargin < m_scrollBar->value()) {
        m_scrollBar->animateToValue(qMax(0, logicalX - xmargin));
    } else if (logicalX > m_scrollBar->value() + m_scrollArea->viewport()->width() - xmargin) {
        m_scrollBar->animateToValue(qMin(logicalX - m_scrollArea->viewport()->width() + xmargin,
            m_scrollBar->maximum()));
    }
}

void TabBarScrollWidget::scrollToLeft(int n, QEasingCurve::Type type)
{
    n = qMax(1, n);
    m_scrollBar->animateToValue(m_scrollBar->value() - n * m_scrollBar->singleStep(), type);
}

void TabBarScrollWidget::scrollToRight(int n, QEasingCurve::Type type)
{
    n = qMax(1, n);
    m_scrollBar->animateToValue(m_scrollBar->value() + n * m_scrollBar->singleStep(), type);
}

void TabBarScrollWidget::scrollToLeftEdge()
{
    m_scrollBar->animateToValue(m_scrollBar->minimum());
}

void TabBarScrollWidget::scrollToRightEdge()
{
    m_scrollBar->animateToValue(m_scrollBar->maximum());
}

void TabBarScrollWidget::setUpLayout()
{
    const int height = m_tabBar->height();

    setFixedHeight(height);
}

void TabBarScrollWidget::updateScrollButtonsState()
{
    m_leftScrollButton->setEnabled(m_scrollBar->value() != m_scrollBar->minimum());
    m_rightScrollButton->setEnabled(m_scrollBar->value() != m_scrollBar->maximum());
}

void TabBarScrollWidget::overFlowChanged(bool overflowed)
{
    bool showScrollButtons = overflowed && m_usesScrollButtons;

    m_leftScrollButton->setVisible(showScrollButtons);
    m_rightScrollButton->setVisible(showScrollButtons);
}

void TabBarScrollWidget::scrollStart()
{
    bool ctrlModifier = QApplication::keyboardModifiers() & Qt::ControlModifier;

    if (sender() == m_leftScrollButton) {
        if (ctrlModifier) {
            scrollToLeftEdge();
        } else {
            scrollToLeft(5, QEasingCurve::Linear);
        }
    } else if (sender() == m_rightScrollButton) {
        if (ctrlModifier) {
            scrollToRightEdge();
        } else {
            scrollToRight(5, QEasingCurve::Linear);
        }
    }
}

void TabBarScrollWidget::scrollByWheel(QWheelEvent* event)
{
    event->accept();

    // Check if direction has changed from last time
    if (m_totalDeltas * event->delta() < 0) {
        m_totalDeltas = 0;
    }

    m_totalDeltas += event->delta();

    // Slower scrolling for horizontal wheel scrolling
    if (event->orientation() == Qt::Horizontal) {
        if (event->delta() > 0) {
            scrollToLeft();
        } else if (event->delta() < 0) {
            scrollToRight();
        }
        return;
    }

    // Faster scrolling with control modifier
    if (event->orientation() == Qt::Vertical && event->modifiers() == Qt::ControlModifier) {
        if (event->delta() > 0) {
            scrollToLeft(10);
        } else if (event->delta() < 0) {
            scrollToRight(10);
        }
        return;
    }

    // Fast scrolling with just wheel scroll
    int factor = qMax(qRound(m_scrollBar->pageStep() / 1.5), m_scrollBar->singleStep());
    if ((event->modifiers() & Qt::ControlModifier) || (event->modifiers() & Qt::ShiftModifier)) {
        factor = m_scrollBar->pageStep();
    }

    int offset = (m_totalDeltas / 120) * factor;
    if (offset != 0) {
        if (isRightToLeft()) {
            m_scrollBar->animateToValue(m_scrollBar->value() + offset);
        } else {
            m_scrollBar->animateToValue(m_scrollBar->value() - offset);
        }

        m_totalDeltas -= (offset / factor) * 120;
    }
}

int TabBarScrollWidget::scrollButtonsWidth() const
{
    // Assumes both buttons have the same width
    return m_leftScrollButton->width();
}

bool TabBarScrollWidget::usesScrollButtons() const
{
    return m_usesScrollButtons;
}

void TabBarScrollWidget::setUsesScrollButtons(bool useButtons)
{
    if (useButtons != m_usesScrollButtons) {
        m_usesScrollButtons = useButtons;
        updateScrollButtonsState();
        m_tabBar->setElideMode(m_tabBar->elideMode());
    }
}

bool TabBarScrollWidget::isOverflowed() const
{
    return m_tabBar->count() > 0 && m_scrollBar->minimum() != m_scrollBar->maximum();
}

int TabBarScrollWidget::tabAt(const QPoint &pos) const
{
    if (m_leftScrollButton->isVisible() && (m_leftScrollButton->rect().contains(pos) ||
        m_rightScrollButton->rect().contains(pos))) {
        return -1;
    }

    return m_tabBar->tabAt(m_tabBar->mapFromGlobal(mapToGlobal(pos)));
}

void TabBarScrollWidget::mouseMoveEvent(QMouseEvent* event)
{
    event->ignore();
}

void TabBarScrollWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    updateScrollButtonsState();
}


