#include "ComboTabBar.h"
#include "TabBarHelper.h"
#include "TabScrollBar.h"
#include "tabicon.h"
#include "CloseButton.h"
#include <QHBoxLayout>
#include <QApplication>
#include <QScrollArea>
#include <QToolTip>
#include <QTimer>
#include <QWheelEvent>
#include <QPainter>

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif


ComboTabBar::ComboTabBar(QWidget* parent)
    : QWidget(parent)
    , m_mainTabBar(0)
    , m_pinnedTabBar(0)
    , m_mainBarOverFlowed(false)
    , m_lastAppliedOverflow(false)
    , m_usesScrollButtons(false)
    , m_blockCurrentChangedSignal(false)
{
    QObject::setObjectName(QSL("tabbarwidget"));

    m_mainTabBar = new TabBarHelper(/*isPinnedTabBar*/ false, this);
    m_pinnedTabBar = new TabBarHelper(/*isPinnedTabBar*/ true, this);
    m_mainTabBarWidget = new TabBarScrollWidget(m_mainTabBar, this);
    m_pinnedTabBarWidget = new TabBarScrollWidget(m_pinnedTabBar, this);

    m_mainTabBar->setScrollArea(m_mainTabBarWidget->scrollArea());
    m_pinnedTabBar->setScrollArea(m_pinnedTabBarWidget->scrollArea());

    connect(m_mainTabBarWidget->scrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setMinimumWidths()));
    connect(m_mainTabBarWidget->scrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(scrollBarValueChanged(int)));
    connect(m_pinnedTabBarWidget->scrollBar(), SIGNAL(rangeChanged(int, int)), this, SLOT(setMinimumWidths()));
    connect(m_pinnedTabBarWidget->scrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(scrollBarValueChanged(int)));
    connect(this, SIGNAL(overFlowChanged(bool)), m_mainTabBarWidget, SLOT(overFlowChanged(bool)));

    m_mainTabBar->setActiveTabBar(true);
    m_pinnedTabBar->setTabsClosable(false);

    m_leftLayout = new QHBoxLayout;
    m_leftLayout->setSpacing(0);
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftContainer = new QWidget(this);
    m_leftContainer->setLayout(m_leftLayout);

    m_rightLayout = new QHBoxLayout;
    m_rightLayout->setSpacing(0);
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightContainer = new QWidget(this);
    m_rightContainer->setLayout(m_rightLayout);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setSpacing(0);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addWidget(m_leftContainer);
    m_mainLayout->addWidget(m_pinnedTabBarWidget);
    m_mainLayout->addWidget(m_mainTabBarWidget);
    m_mainLayout->addWidget(m_rightContainer);
    setLayout(m_mainLayout);

    connect(m_mainTabBar, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentChanged(int)));
    connect(m_mainTabBar, SIGNAL(tabCloseRequested(int)), this, SLOT(slotTabCloseRequested(int)));
    connect(m_mainTabBar, SIGNAL(tabMoved(int, int)), this, SLOT(slotTabMoved(int, int)));

    connect(m_pinnedTabBar, SIGNAL(currentChanged(int)), this, SLOT(slotCurrentChanged(int)));
    connect(m_pinnedTabBar, SIGNAL(tabCloseRequested(int)), this, SLOT(slotTabCloseRequested(int)));
    connect(m_pinnedTabBar, SIGNAL(tabMoved(int, int)), this, SLOT(slotTabMoved(int, int)));

    setAutoFillBackground(false);
    m_mainTabBar->setAutoFillBackground(false);
    m_pinnedTabBar->setAutoFillBackground(false);

    m_mainTabBar->installEventFilter(this);
    m_pinnedTabBar->installEventFilter(this);
    m_leftContainer->installEventFilter(this);
    m_rightContainer->installEventFilter(this);
    m_mainTabBarWidget->installEventFilter(this);
    m_pinnedTabBarWidget->installEventFilter(this);
}

int ComboTabBar::addTab(const QString &text)
{
    return insertTab(-1, text);
}

int ComboTabBar::addTab(const QIcon &icon, const QString &text)
{
    return insertTab(-1, icon, text);
}

int ComboTabBar::insertTab(int index, const QString &text)
{
    return insertTab(index, QIcon(), text);
}

int ComboTabBar::insertTab(int index, const QIcon &icon, const QString &text, bool pinned)
{
    if (pinned) {
        index = m_pinnedTabBar->insertTab(index, icon, text);
    } else {
        index = m_mainTabBar->insertTab(index - pinnedTabsCount(), icon, text);

        if (tabsClosable()) {
            QWidget* closeButton = m_mainTabBar->tabButton(index, closeButtonPosition());
            if ((closeButton && closeButton->objectName() != QLatin1String("combotabbar_tabs_close_button")) || !closeButton) {
                // insert our close button
                insertCloseButton(index + pinnedTabsCount());
                if (closeButton) {
                    closeButton->deleteLater();
                }
            }
        }

        index += pinnedTabsCount();
    }

    updatePinnedTabBarVisibility();
    tabInserted(index);
    setMinimumWidths();

    return index;
}

void ComboTabBar::removeTab(int index)
{
    if (validIndex(index)) {
        setUpdatesEnabled(false);

        localTabBar(index)->removeTab(toLocalIndex(index));
        updatePinnedTabBarVisibility();
        tabRemoved(index);
        setMinimumWidths();

        setUpdatesEnabled(true);
        updateTabBars();
    }
}

void ComboTabBar::moveTab(int from, int to)
{
    if (from >= pinnedTabsCount() && to >= pinnedTabsCount()) {
        m_mainTabBar->moveTab(from - pinnedTabsCount(), to - pinnedTabsCount());
    } else if (from < pinnedTabsCount() && to < pinnedTabsCount()) {
        m_pinnedTabBar->moveTab(from, to);
    }
}

bool ComboTabBar::isTabEnabled(int index) const
{
    return localTabBar(index)->isTabEnabled(toLocalIndex(index));
}

void ComboTabBar::setTabEnabled(int index, bool enabled)
{
    localTabBar(index)->setTabEnabled(toLocalIndex(index), enabled);
}

QColor ComboTabBar::tabTextColor(int index) const
{
    return localTabBar(index)->tabTextColor(toLocalIndex(index));
}

void ComboTabBar::setTabTextColor(int index, const QColor &color)
{
    localTabBar(index)->setTabTextColor(toLocalIndex(index), color);
}

QRect ComboTabBar::tabRect(int index) const
{
    return mapFromLocalTabRect(localTabBar(index)->tabRect(toLocalIndex(index)), localTabBar(index));
}

QRect ComboTabBar::draggedTabRect() const
{
    const QRect r = m_pinnedTabBar->draggedTabRect();
    if (r.isValid()) {
        return mapFromLocalTabRect(r, m_pinnedTabBar);
    }
    return mapFromLocalTabRect(m_mainTabBar->draggedTabRect(), m_mainTabBar);
}

QPixmap ComboTabBar::tabPixmap(int index) const
{
    return localTabBar(index)->tabPixmap(toLocalIndex(index));
}

int ComboTabBar::tabAt(const QPoint &pos) const
{
    QWidget* w = QApplication::widgetAt(mapToGlobal(pos));
    if (!qobject_cast<TabBarHelper*>(w) && !qobject_cast<TabIcon*>(w) && !qobject_cast<MYCloseButton*>(w))
        return -1;

    if (m_pinnedTabBarWidget->geometry().contains(pos)) {
        return m_pinnedTabBarWidget->tabAt(m_pinnedTabBarWidget->mapFromParent(pos));
    } else if (m_mainTabBarWidget->geometry().contains(pos)) {
        int index = m_mainTabBarWidget->tabAt(m_mainTabBarWidget->mapFromParent(pos));
        if (index != -1)
            index += pinnedTabsCount();
        return index;
    }

    return -1;
}

bool ComboTabBar::emptyArea(const QPoint &pos) const
{
    if (tabAt(pos) != -1)
        return false;

    return qobject_cast<TabBarHelper*>(QApplication::widgetAt(mapToGlobal(pos)));
}

int ComboTabBar::mainTabBarCurrentIndex() const
{
    return (m_mainTabBar->currentIndex() == -1 ? -1 : pinnedTabsCount() + m_mainTabBar->currentIndex());
}

int ComboTabBar::currentIndex() const
{
    if (m_pinnedTabBar->isActiveTabBar()) {
        return m_pinnedTabBar->currentIndex();
    } else {
        return (m_mainTabBar->currentIndex() == -1 ? -1 : pinnedTabsCount() + m_mainTabBar->currentIndex());
    }
}

void ComboTabBar::setCurrentIndex(int index)
{
    return localTabBar(index)->setCurrentIndex(toLocalIndex(index));
}

void ComboTabBar::slotCurrentChanged(int index)
{
    if (m_blockCurrentChangedSignal) {
        return;
    }

    if (sender() == m_pinnedTabBar) {
        if (index == -1 && m_mainTabBar->count() > 0) {
            m_mainTabBar->setActiveTabBar(true);
            m_pinnedTabBar->setActiveTabBar(false);
            emit currentChanged(pinnedTabsCount());
        } else {
            m_pinnedTabBar->setActiveTabBar(true);
            m_mainTabBar->setActiveTabBar(false);
            emit currentChanged(index);
        }
    } else {
        if (index == -1 && pinnedTabsCount() > 0) {
            m_pinnedTabBar->setActiveTabBar(true);
            m_mainTabBar->setActiveTabBar(false);
            emit currentChanged(pinnedTabsCount() - 1);
        } else {
            m_mainTabBar->setActiveTabBar(true);
            m_pinnedTabBar->setActiveTabBar(false);
            emit currentChanged(index + pinnedTabsCount());
        }
    }
}

void ComboTabBar::slotTabCloseRequested(int index)
{
    if (sender() == m_pinnedTabBar) {
        emit tabCloseRequested(index);
    } else {
        emit tabCloseRequested(index + pinnedTabsCount());
    }
}

void ComboTabBar::slotTabMoved(int from, int to)
{
    if (sender() == m_pinnedTabBar) {
        emit tabMoved(from, to);
    } else {
        emit tabMoved(from + pinnedTabsCount(), to + pinnedTabsCount());
    }
}

void ComboTabBar::closeTabFromButton()
{
    QWidget* button = qobject_cast<QWidget*>(sender());

    int tabToClose = -1;

    for (int i = 0; i < m_mainTabBar->count(); ++i) {
        if (m_mainTabBar->tabButton(i, closeButtonPosition()) == button) {
            tabToClose = i;
            break;
        }
    }

    if (tabToClose != -1) {
        emit tabCloseRequested(tabToClose + pinnedTabsCount());
    }
}

void ComboTabBar::updateTabBars()
{
    m_mainTabBar->update();
    m_pinnedTabBar->update();
}

void ComboTabBar::emitOverFlowChanged()
{
    if (m_mainBarOverFlowed != m_lastAppliedOverflow) {
        emit overFlowChanged(m_mainBarOverFlowed);
        m_lastAppliedOverflow = m_mainBarOverFlowed;
    }
}

int ComboTabBar::count() const
{
    return pinnedTabsCount() + m_mainTabBar->count();
}

void ComboTabBar::setDrawBase(bool drawTheBase)
{
    m_mainTabBar->setDrawBase(drawTheBase);
    m_pinnedTabBar->setDrawBase(drawTheBase);
}

bool ComboTabBar::drawBase() const
{
    return m_mainTabBar->drawBase();
}

Qt::TextElideMode ComboTabBar::elideMode() const
{
    return m_mainTabBar->elideMode();
}

void ComboTabBar::setElideMode(Qt::TextElideMode elide)
{
    m_mainTabBar->setElideMode(elide);
    m_pinnedTabBar->setElideMode(elide);
}

QString ComboTabBar::tabText(int index) const
{
    return localTabBar(index)->tabText(toLocalIndex(index));
}

void ComboTabBar::setTabText(int index, const QString &text)
{
    localTabBar(index)->setTabText(toLocalIndex(index), text);
}

void ComboTabBar::setTabToolTip(int index, const QString &tip)
{
    localTabBar(index)->setTabToolTip(toLocalIndex(index), tip);
}

QString ComboTabBar::tabToolTip(int index) const
{
    return localTabBar(index)->tabToolTip(toLocalIndex(index));
}

bool ComboTabBar::tabsClosable() const
{
    return m_mainTabBar->tabsClosable();
}

void ComboTabBar::setTabsClosable(bool closable)
{
    if (closable == tabsClosable()) {
        return;
    }

    if (closable) {
        // insert our close button
        for (int i = 0; i < m_mainTabBar->count(); ++i) {
            QWidget* closeButton = m_mainTabBar->tabButton(i, closeButtonPosition());
            if (closeButton) {
                if (closeButton->objectName() == QLatin1String("combotabbar_tabs_close_button")) {
                    continue;
                }
            }

            insertCloseButton(i + pinnedTabsCount());
            if (closeButton) {
                closeButton->deleteLater();
            }
        }
    }
    m_mainTabBar->setTabsClosable(closable);
}

void ComboTabBar::setTabButton(int index, QTabBar::ButtonPosition position, QWidget* widget)
{
    if (widget)
        widget->setMinimumSize(closeButtonSize());
    localTabBar(index)->setTabButton(toLocalIndex(index), position, widget);
}

QWidget* ComboTabBar::tabButton(int index, QTabBar::ButtonPosition position) const
{
    return localTabBar(index)->tabButton(toLocalIndex(index), position);
}

QTabBar::SelectionBehavior ComboTabBar::selectionBehaviorOnRemove() const
{
    return m_mainTabBar->selectionBehaviorOnRemove();
}

void ComboTabBar::setSelectionBehaviorOnRemove(QTabBar::SelectionBehavior behavior)
{
    m_mainTabBar->setSelectionBehaviorOnRemove(behavior);
    m_pinnedTabBar->setSelectionBehaviorOnRemove(behavior);
}

bool ComboTabBar::expanding() const
{
    return m_mainTabBar->expanding();
}

void ComboTabBar::setExpanding(bool enabled)
{
    m_mainTabBar->setExpanding(enabled);
    m_pinnedTabBar->setExpanding(enabled);
}

bool ComboTabBar::isMovable() const
{
    return m_mainTabBar->isMovable();
}

void ComboTabBar::setMovable(bool movable)
{
    m_mainTabBar->setMovable(movable);
    m_pinnedTabBar->setMovable(movable);
}

bool ComboTabBar::documentMode() const
{
    return m_mainTabBar->documentMode();
}

void ComboTabBar::setDocumentMode(bool set)
{
    m_mainTabBar->setDocumentMode(set);
    m_pinnedTabBar->setDocumentMode(set);
}

int ComboTabBar::pinnedTabsCount() const
{
    return m_pinnedTabBar->count();
}

int ComboTabBar::normalTabsCount() const
{
    return m_mainTabBar->count();
}

bool ComboTabBar::isPinned(int index) const
{
    return index >= 0 && index < pinnedTabsCount();
}

void ComboTabBar::setFocusPolicy(Qt::FocusPolicy policy)
{
    QWidget::setFocusPolicy(policy);
    m_mainTabBar->setFocusPolicy(policy);
    m_pinnedTabBar->setFocusPolicy(policy);
}

void ComboTabBar::setObjectName(const QString &name)
{
    m_mainTabBar->setObjectName(name);
    m_pinnedTabBar->setObjectName(name);
}

void ComboTabBar::setMouseTracking(bool enable)
{
    m_mainTabBarWidget->scrollArea()->setMouseTracking(enable);
    m_mainTabBarWidget->setMouseTracking(enable);
    m_mainTabBar->setMouseTracking(enable);

    m_pinnedTabBarWidget->scrollArea()->setMouseTracking(enable);
    m_pinnedTabBarWidget->setMouseTracking(enable);
    m_pinnedTabBar->setMouseTracking(enable);

    QWidget::setMouseTracking(enable);
}

void ComboTabBar::setUpLayout()
{
    int height = qMax(m_mainTabBar->height(), m_pinnedTabBar->height());

    if (height < 1) {
        height = qMax(m_mainTabBar->sizeHint().height(), m_pinnedTabBar->sizeHint().height());
    }

    // We need to setup heights even before m_mainTabBar->height() has correct value
    // So lets just set minimum 5px height
    height = qMax(5, height);

    setFixedHeight(height);
    m_leftContainer->setFixedHeight(height);
    m_rightContainer->setFixedHeight(height);
    m_mainTabBarWidget->setUpLayout();
    m_pinnedTabBarWidget->setUpLayout();

    setMinimumWidths();

    if (isVisible() && height > 5) {
        // ComboTabBar is now visible, we can sync heights of both tabbars
        m_mainTabBar->setFixedHeight(height);
        m_pinnedTabBar->setFixedHeight(height);
    }
}

void ComboTabBar::insertCloseButton(int index)
{
    index -= pinnedTabsCount();
    if (index < 0) {
        return;
    }

    QAbstractButton* closeButton = new MYCloseButton(this);
    closeButton->setFixedSize(closeButtonSize());
    closeButton->setToolTip(m_closeButtonsToolTip);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeTabFromButton()));
    m_mainTabBar->setTabButton(index, closeButtonPosition(), closeButton);
}

void ComboTabBar::setCloseButtonsToolTip(const QString &tip)
{
    m_closeButtonsToolTip = tip;
}

int ComboTabBar::mainTabBarWidth() const
{
    return m_mainTabBar->width();
}

int ComboTabBar::pinTabBarWidth() const
{
    return m_pinnedTabBarWidget->isHidden() ? 0 : m_pinnedTabBarWidget->width();
}

bool ComboTabBar::event(QEvent *event)
{
    const bool res = QWidget::event(event);

    switch (event->type()) {
    case QEvent::ToolTip:
        if (!isDragInProgress() && !isScrollInProgress()) {
            int index = tabAt(mapFromGlobal(QCursor::pos()));
            if (index >= 0)
                QToolTip::showText(QCursor::pos(), tabToolTip(index));
        }
        break;

    case QEvent::Resize:
        ensureVisible();
        break;

    case QEvent::Show:
        if (!event->spontaneous())
            QTimer::singleShot(0, this, &ComboTabBar::setUpLayout);
        break;

    case QEvent::Enter:
    case QEvent::Leave:
        // Make sure tabs are painted with correct mouseover state
        QTimer::singleShot(100, this, &ComboTabBar::updateTabBars);
        break;

    default:
        break;
    }

    return res;
}

void ComboTabBar::wheelEvent(QWheelEvent* event)
{
    event->accept();

    //if (qzSettings->alwaysSwitchTabsWithWheel || (!m_mainTabBarWidget->isOverflowed() && !m_pinnedTabBarWidget->isOverflowed())) {
    if ((!m_mainTabBarWidget->isOverflowed() && !m_pinnedTabBarWidget->isOverflowed())) {
        m_wheelHelper.processEvent(event);
        while (WheelHelper::Direction direction = m_wheelHelper.takeDirection()) {
            switch (direction) {
            case WheelHelper::WheelUp:
            case WheelHelper::WheelLeft:
                setCurrentNextEnabledIndex(-1);
                break;

            case WheelHelper::WheelDown:
            case WheelHelper::WheelRight:
                setCurrentNextEnabledIndex(1);
                break;

            default:
                break;
            }
        }
        return;
    }

    if (m_mainTabBarWidget->underMouse()) {
        if (m_mainTabBarWidget->isOverflowed()) {
            m_mainTabBarWidget->scrollByWheel(event);
        } else if (m_pinnedTabBarWidget->isOverflowed()) {
            m_pinnedTabBarWidget->scrollByWheel(event);
        }
    } else if (m_pinnedTabBarWidget->underMouse()) {
        if (m_pinnedTabBarWidget->isOverflowed()) {
            m_pinnedTabBarWidget->scrollByWheel(event);
        } else if (m_mainTabBarWidget->isOverflowed()) {
            m_mainTabBarWidget->scrollByWheel(event);
        }
    }
}

bool ComboTabBar::eventFilter(QObject* obj, QEvent* ev)
{
    if (obj == m_mainTabBar && ev->type() == QEvent::Resize) {
        QResizeEvent* event = static_cast<QResizeEvent*>(ev);
        if (event->oldSize().height() != event->size().height()) {
            setUpLayout();
        }
    }

    // Handle wheel events exclusively in ComboTabBar
    if (ev->type() == QEvent::Wheel) {
        wheelEvent(static_cast<QWheelEvent*>(ev));
        return true;
    }

    return QWidget::eventFilter(obj, ev);
}

void ComboTabBar::paintEvent(QPaintEvent* ev)
{
    Q_UNUSED(ev);

    // This is needed to apply style sheets
    QStyleOption option;
    option.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &p, this);

#ifndef Q_OS_MACOS
    // Draw tabbar base even on parts of ComboTabBar that are not directly QTabBar
    QStyleOptionTabBarBase opt;
    TabBarHelper::initStyleBaseOption(&opt, m_mainTabBar, size());

    // Left container
    opt.rect.setX(m_leftContainer->x());
    opt.rect.setWidth(m_leftContainer->width());
    style()->drawPrimitive(QStyle::PE_FrameTabBarBase, &opt, &p);

    // Right container
    opt.rect.setX(m_rightContainer->x());
    opt.rect.setWidth(m_rightContainer->width());
    style()->drawPrimitive(QStyle::PE_FrameTabBarBase, &opt, &p);

    if (m_mainBarOverFlowed) {
        const int scrollButtonWidth = m_mainTabBarWidget->scrollButtonsWidth();

        // Left scroll button
        opt.rect.setX(m_mainTabBarWidget->x());
        opt.rect.setWidth(scrollButtonWidth);
        style()->drawPrimitive(QStyle::PE_FrameTabBarBase, &opt, &p);

        // Right scroll button
        opt.rect.setX(m_mainTabBarWidget->x() + m_mainTabBarWidget->width() - scrollButtonWidth);
        opt.rect.setWidth(scrollButtonWidth);
        style()->drawPrimitive(QStyle::PE_FrameTabBarBase, &opt, &p);
    }

    // Draw base even when main tabbar is empty
    if (normalTabsCount() == 0) {
        opt.rect.setX(m_mainTabBarWidget->x());
        opt.rect.setWidth(m_mainTabBarWidget->width());
        style()->drawPrimitive(QStyle::PE_FrameTabBarBase, &opt, &p);
    }
#endif
}

int ComboTabBar::comboTabBarPixelMetric(ComboTabBar::SizeType sizeType) const
{
    switch (sizeType) {
    case ExtraReservedWidth:
        return 0;

    case NormalTabMaximumWidth:
        return 150;

    case ActiveTabMinimumWidth:
    case NormalTabMinimumWidth:
    case OverflowedTabWidth:
        return 100;

    case PinnedTabWidth:
        return 30;

    default:
        break;
    }

    return -1;
}

QTabBar::ButtonPosition ComboTabBar::iconButtonPosition() const
{
    return (closeButtonPosition() == QTabBar::RightSide ? QTabBar::LeftSide : QTabBar::RightSide);
}

QTabBar::ButtonPosition ComboTabBar::closeButtonPosition() const
{
    return (QTabBar::ButtonPosition)style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, 0, m_mainTabBar);
}

QSize ComboTabBar::iconButtonSize() const
{
    QSize s = closeButtonSize();
    s.setWidth(qMax(16, s.width()));
    s.setHeight(qMax(16, s.height()));
    return s;
}

QSize ComboTabBar::closeButtonSize() const
{
    int width = style()->pixelMetric(QStyle::PM_TabCloseIndicatorWidth, 0, this);
    int height = style()->pixelMetric(QStyle::PM_TabCloseIndicatorHeight, 0, this);
    return QSize(width, height);
}

bool ComboTabBar::validIndex(int index) const
{
    return (index >= 0 && index < count());
}

void ComboTabBar::setCurrentNextEnabledIndex(int offset)
{
    for (int index = currentIndex() + offset; validIndex(index); index += offset) {
        if (isTabEnabled(index)) {
            setCurrentIndex(index);
            break;
        }
    }
}

bool ComboTabBar::usesScrollButtons() const
{
    return m_mainTabBarWidget->usesScrollButtons();
}

void ComboTabBar::setUsesScrollButtons(bool useButtons)
{
    m_mainTabBarWidget->setUsesScrollButtons(useButtons);
}

void ComboTabBar::showDropIndicator(int index, DropIndicatorPosition position)
{
    clearDropIndicator();
    localTabBar(index)->showDropIndicator(toLocalIndex(index), position);
}

void ComboTabBar::clearDropIndicator()
{
    m_mainTabBar->clearDropIndicator();
    m_pinnedTabBar->clearDropIndicator();
}

bool ComboTabBar::isDragInProgress() const
{
    return m_mainTabBar->isDragInProgress() || m_pinnedTabBar->isDragInProgress();
}

bool ComboTabBar::isScrollInProgress() const
{
    return m_mainTabBarWidget->scrollBar()->isScrolling() || m_pinnedTabBarWidget->scrollBar()->isScrolling();
}

bool ComboTabBar::isMainBarOverflowed() const
{
    return m_mainBarOverFlowed;
}

int ComboTabBar::cornerWidth(Qt::Corner corner) const
{
    if (corner == Qt::TopLeftCorner) {
        return m_leftContainer->width();
    } else if (corner == Qt::TopRightCorner) {
        return m_rightContainer->width();
    }

    qFatal("ComboTabBar::cornerWidth Only TopLeft and TopRight corners are implemented!");
    return -1;
}

void ComboTabBar::addCornerWidget(QWidget* widget, Qt::Corner corner)
{
    if (corner == Qt::TopLeftCorner) {
        m_leftLayout->addWidget(widget);
    } else if (corner == Qt::TopRightCorner) {
        m_rightLayout->addWidget(widget);
    } else {
        qFatal("ComboTabBar::addCornerWidget Only TopLeft and TopRight corners are implemented!");
    }
}

// static
int ComboTabBar::slideAnimationDuration()
{
    // taken from qtabbar_p.h
    return 250;
}

void ComboTabBar::ensureVisible(int index, int xmargin)
{
    if (index == -1) {
        index = currentIndex();
    }

    if (index < pinnedTabsCount()) {
        if (xmargin == -1) {
            xmargin = qMax(20, comboTabBarPixelMetric(PinnedTabWidth));
        }
        m_pinnedTabBarWidget->ensureVisible(index, xmargin);
    } else {
        if (xmargin == -1) {
            xmargin = comboTabBarPixelMetric(OverflowedTabWidth);
        }
        index -= pinnedTabsCount();
        m_mainTabBarWidget->ensureVisible(index, xmargin);
    }
}

QSize ComboTabBar::tabSizeHint(int index, bool fast) const
{
    Q_UNUSED(fast)

        return localTabBar(index)->baseClassTabSizeHint(toLocalIndex(index));
}

void ComboTabBar::tabInserted(int index)
{
    Q_UNUSED(index)
}

void ComboTabBar::tabRemoved(int index)
{
    Q_UNUSED(index)
}

TabBarHelper* ComboTabBar::mainTabBar() const
{
    return m_mainTabBar;
}

TabBarHelper* ComboTabBar::localTabBar(int index) const
{
    if (index < 0 || index >= pinnedTabsCount()) {
        return m_mainTabBar;
    } else {
        return m_pinnedTabBar;
    }
}

int ComboTabBar::toLocalIndex(int globalIndex) const
{
    if (globalIndex < 0) {
        return -1;
    }

    if (globalIndex >= pinnedTabsCount()) {
        return globalIndex - pinnedTabsCount();
    } else {
        return globalIndex;
    }
}

QRect ComboTabBar::mapFromLocalTabRect(const QRect &rect, QWidget *tabBar) const
{
    if (!rect.isValid()) {
        return rect;
    }

    QRect r = rect;

    if (tabBar == m_mainTabBar) {
        r.moveLeft(r.x() + mapFromGlobal(m_mainTabBar->mapToGlobal(QPoint(0, 0))).x());
        QRect widgetRect = m_mainTabBarWidget->scrollArea()->viewport()->rect();
        widgetRect.moveLeft(widgetRect.x() + mapFromGlobal(m_mainTabBarWidget->scrollArea()->viewport()->mapToGlobal(QPoint(0, 0))).x());
        r = r.intersected(widgetRect);
    } else {
        r.moveLeft(r.x() + mapFromGlobal(m_pinnedTabBar->mapToGlobal(QPoint(0, 0))).x());
        QRect widgetRect = m_pinnedTabBarWidget->scrollArea()->viewport()->rect();
        widgetRect.moveLeft(widgetRect.x() + mapFromGlobal(m_pinnedTabBarWidget->scrollArea()->viewport()->mapToGlobal(QPoint(0, 0))).x());
        r = r.intersected(widgetRect);
    }

    return r;
}

void ComboTabBar::updatePinnedTabBarVisibility()
{
    m_pinnedTabBarWidget->setVisible(pinnedTabsCount() > 0);
}

void ComboTabBar::setMinimumWidths()
{
    if (!isVisible() || comboTabBarPixelMetric(PinnedTabWidth) < 0) {
        return;
    }

    const int tabBarsSpacing = 3; // To distinguish tabbars
    int pinnedTabBarWidth = pinnedTabsCount() * comboTabBarPixelMetric(PinnedTabWidth);
    m_pinnedTabBar->setMinimumWidth(pinnedTabBarWidth);
    m_pinnedTabBarWidget->setFixedWidth(pinnedTabBarWidth + tabBarsSpacing);

    // Width that is needed by main tabbar
    int mainTabBarWidth = comboTabBarPixelMetric(NormalTabMinimumWidth) * (m_mainTabBar->count() - 1) +
        comboTabBarPixelMetric(ActiveTabMinimumWidth) +
        comboTabBarPixelMetric(ExtraReservedWidth);

    // This is the full width that would be needed for the tabbar (including pinned tabbar and corner widgets)
    int realTabBarWidth = mainTabBarWidth + m_pinnedTabBarWidget->width() +
        cornerWidth(Qt::TopLeftCorner) +
        cornerWidth(Qt::TopRightCorner);

    // Does it fit in our widget?
    if (realTabBarWidth <= width()) {
        if (m_mainBarOverFlowed) {
            m_mainBarOverFlowed = false;
            QTimer::singleShot(0, this, SLOT(emitOverFlowChanged()));
        }

        m_mainTabBar->useFastTabSizeHint(false);
        m_mainTabBar->setMinimumWidth(mainTabBarWidth);
    } else {
        if (!m_mainBarOverFlowed) {
            m_mainBarOverFlowed = true;
            QTimer::singleShot(0, this, SLOT(emitOverFlowChanged()));
        }

        // All tabs have now same width, we can use fast tabSizeHint
        m_mainTabBar->useFastTabSizeHint(true);
        m_mainTabBar->setMinimumWidth(m_mainTabBar->count() * comboTabBarPixelMetric(OverflowedTabWidth));
    }
}