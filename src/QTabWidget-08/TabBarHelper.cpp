#include "TabBarHelper.h"
#include "ComboTabBar.h"
#include "ctrl_common.h"
#include <QPainter>
#include <QScrollArea>
#include <QEvent>
#include <QStylePainter>
#include <QMouseEvent>
#include <QApplication>

TabBarHelper::TabBarHelper(bool isPinnedTabBar, ComboTabBar* comboTabBar)
    : QTabBar(comboTabBar)
    , m_comboTabBar(comboTabBar)
    , m_scrollArea(0)
    , m_pressedIndex(-1)
    , m_dragInProgress(false)
    , m_activeTabBar(false)
    , m_isPinnedTabBar(isPinnedTabBar)
    , m_useFastTabSizeHint(false)
{
}

int TabBarHelper::tabPadding() const
{
    return m_tabPadding;
}

void TabBarHelper::setTabPadding(int padding)
{
    m_tabPadding = padding;
}

QColor TabBarHelper::baseColor() const
{
    return m_baseColor;
}

void TabBarHelper::setBaseColor(const QColor &color)
{
    m_baseColor = color;
}

void TabBarHelper::setTabButton(int index, QTabBar::ButtonPosition position, QWidget* widget)
{
    QTabBar::setTabButton(index, position, widget);
}

QSize TabBarHelper::tabSizeHint(int index) const
{
    if (this == m_comboTabBar->mainTabBar()) {
        index += m_comboTabBar->pinnedTabsCount();
    }
    return m_comboTabBar->tabSizeHint(index, m_useFastTabSizeHint);
}

QSize TabBarHelper::baseClassTabSizeHint(int index) const
{
    return QTabBar::tabSizeHint(index);
}

QRect TabBarHelper::draggedTabRect() const
{
    if (!m_dragInProgress) {
        return QRect();
    }

    QStyleOptionTab tab;
    initStyleOption(&tab, m_pressedIndex);

    const int tabDragOffset = dragOffset(&tab, m_pressedIndex);
    if (tabDragOffset != 0) {
        tab.rect.moveLeft(tab.rect.x() + tabDragOffset);
    }
    return tab.rect;
}

QPixmap TabBarHelper::tabPixmap(int index) const
{
    QStyleOptionTab tab;
    initStyleOption(&tab, index);

    tab.state &= ~QStyle::State_MouseOver;
    tab.position = QStyleOptionTab::OnlyOneTab;
    tab.leftButtonSize = QSize();
    tab.rightButtonSize = QSize();

    QWidget *iconButton = tabButton(index, m_comboTabBar->iconButtonPosition());
    QWidget *closeButton = tabButton(index, m_comboTabBar->closeButtonPosition());

    if (iconButton) {
        const QPixmap pix = iconButton->grab();
        if (!pix.isNull()) {
            tab.icon = pix;
            tab.iconSize = pix.size() / pix.devicePixelRatioF();
        }
    }

    if (closeButton) {
        const int width = tab.fontMetrics.width(tab.text) + closeButton->width();
        tab.text = tab.fontMetrics.elidedText(tabText(index), Qt::ElideRight, width);
    }

    QPixmap out(tab.rect.size() * devicePixelRatioF());
    out.setDevicePixelRatio(devicePixelRatioF());
    out.fill(Qt::transparent);
    tab.rect = QRect(QPoint(0, 0), tab.rect.size());

    QPainter p(&out);
    style()->drawControl(QStyle::CE_TabBarTab, &tab, &p, this);
    p.end();

    return out;
}

bool TabBarHelper::isActiveTabBar()
{
    return m_activeTabBar;
}

void TabBarHelper::setActiveTabBar(bool activate)
{
    if (m_activeTabBar != activate) {
        m_activeTabBar = activate;

        // If the last tab in a tabbar is closed, the selection jumps to the other
        // tabbar. The stacked widget automatically selects the next tab, which is
        // either the last tab in pinned tabbar or the first one in main tabbar.

        if (!m_activeTabBar) {
            m_comboTabBar->m_blockCurrentChangedSignal = true;
            setCurrentIndex(m_isPinnedTabBar ? count() - 1 : 0);
            m_comboTabBar->m_blockCurrentChangedSignal = false;
        }

        update();
    }
}

void TabBarHelper::removeTab(int index)
{
    // Removing tab in inactive tabbar will change current index and thus
    // changing active tabbar, which is really not wanted.
    // Also removing tab will cause a duplicate call to ComboTabBar::slotCurrentChanged()
    m_comboTabBar->m_blockCurrentChangedSignal = true;

    QTabBar::removeTab(index);

    m_comboTabBar->m_blockCurrentChangedSignal = false;
}

void TabBarHelper::setScrollArea(QScrollArea* scrollArea)
{
    m_scrollArea = scrollArea;
}

void TabBarHelper::useFastTabSizeHint(bool enabled)
{
    m_useFastTabSizeHint = enabled;
}

void TabBarHelper::showDropIndicator(int index, ComboTabBar::DropIndicatorPosition position)
{
    m_dropIndicatorIndex = index;
    m_dropIndicatorPosition = position;
    update();
}

void TabBarHelper::clearDropIndicator()
{
    m_dropIndicatorIndex = -1;
    update();
}

bool TabBarHelper::isDisplayedOnViewPort(int globalLeft, int globalRight)
{
    bool isVisible = true;

    if (m_scrollArea) {
        if (globalRight < m_scrollArea->viewport()->mapToGlobal(QPoint(0, 0)).x() ||
            globalLeft > m_scrollArea->viewport()->mapToGlobal(m_scrollArea->viewport()->rect().topRight()).x()
            ) {
            isVisible = false;
        }
    }

    return isVisible;
}

bool TabBarHelper::isDragInProgress() const
{
    return m_dragInProgress;
}

void TabBarHelper::setCurrentIndex(int index)
{
    if (index == currentIndex() && !m_activeTabBar) {
        emit currentChanged(currentIndex());
    }

    QTabBar::setCurrentIndex(index);
}

bool TabBarHelper::event(QEvent* ev)
{
    switch (ev->type()) {
    case QEvent::ToolTip:
        ev->ignore();
        return false;

    default:
        break;
    }

    QTabBar::event(ev);
    ev->ignore();
    return false;
}

// Hack to get dragOffset from QTabBar internals
int TabBarHelper::dragOffset(QStyleOptionTab *option, int tabIndex) const
{
    QRect rect;
    QWidget *button = tabButton(tabIndex, QTabBar::LeftSide);
    if (button) {
        rect = style()->subElementRect(QStyle::SE_TabBarTabLeftButton, option, this);
    }
    if (!rect.isValid()) {
        button = tabButton(tabIndex, QTabBar::RightSide);
        rect = style()->subElementRect(QStyle::SE_TabBarTabRightButton, option, this);
    }
    if (!button || !rect.isValid()) {
        return 0;
    }
    return button->pos().x() - rect.topLeft().x();
}

// Taken from qtabbar.cpp
void TabBarHelper::initStyleBaseOption(QStyleOptionTabBarBase *optTabBase, QTabBar* tabbar, QSize size)
{
    QStyleOptionTab tabOverlap;
    tabOverlap.shape = tabbar->shape();
    int overlap = tabbar->style()->pixelMetric(QStyle::PM_TabBarBaseOverlap, &tabOverlap, tabbar);
    QWidget* theParent = tabbar->parentWidget();
    optTabBase->init(tabbar);
    optTabBase->shape = tabbar->shape();
    optTabBase->documentMode = tabbar->documentMode();
    if (theParent && overlap > 0) {
        QRect rect;
        switch (tabOverlap.shape) {
        case QTabBar::RoundedNorth:
        case QTabBar::TriangularNorth:
            rect.setRect(0, size.height() - overlap, size.width(), overlap);
            break;
        case QTabBar::RoundedSouth:
        case QTabBar::TriangularSouth:
            rect.setRect(0, 0, size.width(), overlap);
            break;
        case QTabBar::RoundedEast:
        case QTabBar::TriangularEast:
            rect.setRect(0, 0, overlap, size.height());
            break;
        case QTabBar::RoundedWest:
        case QTabBar::TriangularWest:
            rect.setRect(size.width() - overlap, 0, overlap, size.height());
            break;
        }
        optTabBase->rect = rect;
    }
}

// Adapted from qtabbar.cpp
// Note: doesn't support vertical tabs
void TabBarHelper::paintEvent(QPaintEvent *)
{
    QStyleOptionTabBarBase optTabBase;
    initStyleBaseOption(&optTabBase, this, size());

    QStylePainter p(this);
    int selected = currentIndex();

    for (int i = 0; i < count(); ++i) {
        optTabBase.tabBarRect |= tabRect(i);
    }

    if (m_activeTabBar) {
        optTabBase.selectedTabRect = tabRect(selected);
    }

    if (drawBase()) {
        p.drawPrimitive(QStyle::PE_FrameTabBarBase, optTabBase);
    }

    const QPoint cursorPos = QCursor::pos();
    int indexUnderMouse = isDisplayedOnViewPort(cursorPos.x(), cursorPos.x()) ? tabAt(mapFromGlobal(cursorPos)) : -1;

    for (int i = 0; i < count(); ++i) {
        if (i == selected) {
            continue;
        }

        QStyleOptionTab tab;
        initStyleOption(&tab, i);

        const int tabDragOffset = dragOffset(&tab, i);
        if (tabDragOffset != 0) {
            tab.rect.moveLeft(tab.rect.x() + tabDragOffset);
        }

        // Don't bother drawing a tab if the entire tab is outside of the visible tab bar.
        if (!isDisplayedOnViewPort(mapToGlobal(tab.rect.topLeft()).x(), mapToGlobal(tab.rect.topRight()).x())) {
            continue;
        }

        if (!m_activeTabBar) {
            tab.selectedPosition = QStyleOptionTab::NotAdjacent;
        }

        if (!(tab.state & QStyle::State_Enabled)) {
            tab.palette.setCurrentColorGroup(QPalette::Disabled);
        }

        // Update mouseover state when scrolling
        if (!m_dragInProgress && i == indexUnderMouse) {
            tab.state |= QStyle::State_MouseOver;
        } else {
            tab.state &= ~QStyle::State_MouseOver;
        }

        p.drawControl(QStyle::CE_TabBarTab, tab);
    }

    // Draw the selected tab last to get it "on top"
    if (selected >= 0) {
        QStyleOptionTab tab;
        initStyleOption(&tab, selected);

        const int tabDragOffset = dragOffset(&tab, selected);
        if (tabDragOffset != 0) {
            tab.rect.moveLeft(tab.rect.x() + tabDragOffset);
        }

        // Update mouseover state when scrolling
        if (selected == indexUnderMouse) {
            tab.state |= QStyle::State_MouseOver;
        } else {
            tab.state &= ~QStyle::State_MouseOver;
        }

        if (!m_activeTabBar) {
            // If this is inactive tab, we still need to draw selected tab outside the tabbar
            // Some themes (eg. Oxygen) draws line under tabs with selected tab
            // Let's just move it outside rect(), it appears to work
            QStyleOptionTab tb = tab;
            tb.rect.moveRight((rect().x() + rect().width()) * 2);
            p.drawControl(QStyle::CE_TabBarTab, tb);

            // Draw the tab without selected state
            tab.state = tab.state & ~QStyle::State_Selected;
        }

        if (!m_movingTab || !m_movingTab->isVisible()) {
            p.drawControl(QStyle::CE_TabBarTab, tab);
        } else {
            int taboverlap = style()->pixelMetric(QStyle::PM_TabBarTabOverlap, nullptr, this);
            m_movingTab->setGeometry(tab.rect.adjusted(-taboverlap, 0, taboverlap, 0));

            QRect grabRect = tabRect(selected);
            grabRect.adjust(-taboverlap, 0, taboverlap, 0);
            QPixmap grabImage(grabRect.size() * devicePixelRatioF());
            grabImage.setDevicePixelRatio(devicePixelRatioF());
            grabImage.fill(Qt::transparent);
            QStylePainter p(&grabImage, this);
            p.initFrom(this);
            if (tabDragOffset != 0) {
                tab.position = QStyleOptionTab::OnlyOneTab;
            }
            tab.rect.moveTopLeft(QPoint(taboverlap, 0));
            p.drawControl(QStyle::CE_TabBarTab, tab);
            m_movingTab->m_pixmap = grabImage;
            m_movingTab->update();
        }
    }

    // Draw drop indicator
    if (m_dropIndicatorIndex != -1) {
        const QRect tr = tabRect(m_dropIndicatorIndex);
        QRect r;
        if (m_dropIndicatorPosition == ComboTabBar::BeforeTab) {
            r = QRect(qMax(0, tr.left() - 1), tr.top(), 3, tr.height());
        } else {
            const int rightOffset = m_dropIndicatorIndex == count() - 1 ? -2 : 0;
            r = QRect(tr.right() + rightOffset, tr.top(), 3, tr.height());
        }
        QzTools::paintDropIndicator(this, r);
    }
}

void TabBarHelper::mousePressEvent(QMouseEvent* event)
{
    event->ignore();
    if (event->buttons() == Qt::LeftButton) {
        m_pressedIndex = tabAt(event->pos());
        if (m_pressedIndex != -1) {
            m_dragStartPosition = event->pos();
            // virtualize selecting tab by click
            if (m_pressedIndex == currentIndex() && !m_activeTabBar) {
                emit currentChanged(currentIndex());
            }
        }
    }

    QTabBar::mousePressEvent(event);
}

void TabBarHelper::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_dragInProgress && m_pressedIndex != -1) {
        if ((event->pos() - m_dragStartPosition).manhattanLength() > QApplication::startDragDistance()) {
            m_dragInProgress = true;
        }
    }

    QTabBar::mouseMoveEvent(event);

    // Hack to find QMovableTabWidget
    if (m_dragInProgress && !m_movingTab) {
        const auto objects = children();
        const int taboverlap = style()->pixelMetric(QStyle::PM_TabBarTabOverlap, nullptr, this);
        QRect grabRect = tabRect(currentIndex());
        grabRect.adjust(-taboverlap, 0, taboverlap, 0);
        for (QObject *object : objects) {
            QWidget *widget = qobject_cast<QWidget*>(object);
            if (widget && widget->geometry() == grabRect) {
                m_movingTab = static_cast<QMovableTabWidget*>(widget);
                break;
            }
        }
    }

    // Don't allow to move tabs outside of tabbar
    if (m_dragInProgress && m_movingTab) {
        // FIXME: This doesn't work at all with RTL...
        if (isRightToLeft()) {
            return;
        }
        QRect r = tabRect(m_pressedIndex);
        r.moveLeft(r.x() + (event->pos().x() - m_dragStartPosition.x()));
        bool sendEvent = false;
        int diff = r.topRight().x() - tabRect(count() - 1).topRight().x();
        if (diff > 0) {
            sendEvent = true;
        } else {
            diff = r.topLeft().x() - tabRect(0).topLeft().x();
            if (diff < 0) {
                sendEvent = true;
            }
        }
        if (sendEvent) {
            QPoint pos = event->pos();
            pos.setX(pos.x() - diff);
            QMouseEvent ev(event->type(), pos, event->button(), event->buttons(), event->modifiers());
            QTabBar::mouseMoveEvent(&ev);
        }
    }
}

void TabBarHelper::mouseReleaseEvent(QMouseEvent* event)
{
    event->ignore();

    if (event->button() == Qt::LeftButton) {
        m_pressedIndex = -1;
        m_dragInProgress = false;
        m_dragStartPosition = QPoint();
    }

    QTabBar::mouseReleaseEvent(event);

    update();
}

void TabBarHelper::initStyleOption(QStyleOptionTab* option, int tabIndex) const
{
    QTabBar::initStyleOption(option, tabIndex);

    // Workaround zero padding when tabs are styled using style sheets
    if (m_tabPadding) {
        const QRect textRect = style()->subElementRect(QStyle::SE_TabBarTabText, option, this);
        const int width = textRect.width() - 2 * m_tabPadding;
        option->text = option->fontMetrics.elidedText(tabText(tabIndex), elideMode(), width, Qt::TextShowMnemonic);
    }

    // Bespin doesn't highlight current tab when there is only one tab in tabbar
    static int isBespin = -1;

    /*if (isBespin == -1)
    isBespin = mApp->styleName() == QL1S("bespin");*/

    if (!isBespin)
        return;

    int index = m_isPinnedTabBar ? tabIndex : m_comboTabBar->pinnedTabsCount() + tabIndex;

    if (m_comboTabBar->count() > 1) {
        if (index == 0)
            option->position = QStyleOptionTab::Beginning;
        else if (index == m_comboTabBar->count() - 1)
            option->position = QStyleOptionTab::End;
        else
            option->position = QStyleOptionTab::Middle;
    } else {
        option->position = QStyleOptionTab::OnlyOneTab;
    }
}