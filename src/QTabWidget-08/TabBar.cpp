#include "tabbar.h"
#include "TabScrollBar.h"
#include "CloseButton.h"


#include <QDebug>
#include <QIcon>
#include <QHBoxLayout>
#include <QStylePainter>
#include <QStyleOptionTabV3>
#include <QStyleOptionTabBarBaseV2>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QTimer>
#include <QTabBar>
#include <QMouseEvent>
#include <QApplication>
#include <QToolTip>
#include <QWheelEvent>
#include <QMimeData>


////////////////////////////////////////////////////////////////////////////////////////////////////////



#define MIMETYPE QSL("application/falkon.tabbar.tab")

class TabBarTabMetrics : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(int normalMaxWidth READ normalMaxWidth WRITE setNormalMaxWidth)
        Q_PROPERTY(int normalMinWidth READ normalMinWidth WRITE setNormalMinWidth)
        Q_PROPERTY(int activeMinWidth READ activeMinWidth WRITE setActiveMinWidth)
        Q_PROPERTY(int overflowedWidth READ overflowedWidth WRITE setOverflowedWidth)
        Q_PROPERTY(int pinnedWidth READ pinnedWidth WRITE setPinnedWidth)

public:
    void init()
    {
        if (!m_metrics.isEmpty()) {
            return;
        }
        m_metrics[0] = 250;
        m_metrics[1] = 100;
        m_metrics[2] = 100;
        m_metrics[3] = 100;
        m_metrics[4] = -1; // Will be initialized from TabBar
    }

    int normalMaxWidth() const { return m_metrics.value(0); }
    void setNormalMaxWidth(int value) { m_metrics[0] = value; }

    int normalMinWidth() const { return m_metrics.value(1); }
    void setNormalMinWidth(int value) { m_metrics[1] = value; }

    int activeMinWidth() const { return m_metrics.value(2); }
    void setActiveMinWidth(int value) { m_metrics[2] = value; }

    int overflowedWidth() const { return m_metrics.value(3); }
    void setOverflowedWidth(int value) { m_metrics[3] = value; }

    int pinnedWidth() const { return m_metrics.value(4); }
    void setPinnedWidth(int value) { m_metrics[4] = value; }

private:
    QHash<int, int> m_metrics;
};

Q_GLOBAL_STATIC(TabBarTabMetrics, tabMetrics)

MYTabBar::MYTabBar(BrowserWindow* window, TabWidget* tabWidget)
    : ComboTabBar()
    , m_window(window)
    , m_tabWidget(tabWidget)
    , m_hideTabBarWithOneTab(false)
    , m_showCloseOnInactive(0)
    , m_normalTabWidth(0)
    , m_activeTabWidth(0)
    , m_forceHidden(false)
{
    setObjectName("tabbar");
    setElideMode(Qt::ElideRight);
    setFocusPolicy(Qt::NoFocus);
    setTabsClosable(false);
    setMouseTracking(true);
    setDocumentMode(true);
    setAcceptDrops(true);
    setDrawBase(false);
    setMovable(true);

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));

    // ComboTabBar features
    setUsesScrollButtons(true);
    //setCloseButtonsToolTip(BrowserWindow::tr("Close Tab"));
    connect(this, SIGNAL(overFlowChanged(bool)), this, SLOT(overflowChanged(bool)));

    tabMetrics()->init();

    //if (mApp->isPrivate()) {
    //    QLabel* privateBrowsing = new QLabel(this);
    //    privateBrowsing->setObjectName(QSL("private-browsing-icon"));
    //    privateBrowsing->setPixmap(IconProvider::privateBrowsingIcon().pixmap(16));
    //    privateBrowsing->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //    privateBrowsing->setFixedWidth(30);
    //    addCornerWidget(privateBrowsing, Qt::TopLeftCorner);
    //}
}

void MYTabBar::loadSettings()
{
    //Settings settings;
    //settings.beginGroup("Browser-Tabs-Settings");
    //m_hideTabBarWithOneTab = settings.value("hideTabsWithOneTab", false).toBool();
    //bool activateLastTab = settings.value("ActivateLastTabWhenClosingActual", false).toBool();
    //m_showCloseOnInactive = settings.value("showCloseOnInactiveTabs", 0).toInt(0);
    //settings.endGroup();

    //setSelectionBehaviorOnRemove(activateLastTab ? QTabBar::SelectPreviousTab : QTabBar::SelectRightTab);
    //setVisible(!(count() <= 1 && m_hideTabBarWithOneTab));

    setUpLayout();
}

TabWidget* MYTabBar::tabWidget() const
{
    return m_tabWidget;
}

void MYTabBar::setVisible(bool visible)
{
    if (m_forceHidden) {
        ComboTabBar::setVisible(false);
        return;
    }

    // Make sure to honor user preference
    if (visible) {
        visible = !(count() <= 1 && m_hideTabBarWithOneTab);
    }

    ComboTabBar::setVisible(visible);
}

void MYTabBar::setForceHidden(bool hidden)
{
    m_forceHidden = hidden;
    setVisible(!m_forceHidden);
}

void MYTabBar::overflowChanged(bool overflowed)
{
    // Make sure close buttons on inactive tabs are hidden
    // This is needed for when leaving fullscreen from non-overflowed to overflowed state
    if (overflowed && m_showCloseOnInactive != 1) {
        setTabsClosable(false);
        showCloseButton(currentIndex());
    }
}

QSize MYTabBar::tabSizeHint(int index, bool fast) const
{
    //if (!m_window->isVisible()) {
    //    // Don't calculate it when window is not visible
    //    // It produces invalid size anyway
    //    return QSize(-1, -1);
    //}

    //const int pinnedTabWidth = comboTabBarPixelMetric(ComboTabBar::PinnedTabWidth);
    //const int minTabWidth = comboTabBarPixelMetric(ComboTabBar::NormalTabMinimumWidth);

    //QSize size = ComboTabBar::tabSizeHint(index);

    //// The overflowed tabs have same size and we can use this fast method
    //if (fast) {
    //    size.setWidth(index >= pinnedTabsCount() ? minTabWidth : pinnedTabWidth);
    //    return size;
    //}

    //WebTab* webTab = qobject_cast<WebTab*>(m_tabWidget->widget(index));
    //TabBar* tabBar = const_cast <TabBar*>(this);

    //if (webTab && webTab->isPinned()) {
    //    size.setWidth(pinnedTabWidth);
    //} else {
    //    int availableWidth = mainTabBarWidth() - comboTabBarPixelMetric(ExtraReservedWidth);

    //    if (availableWidth < 0) {
    //        return QSize(-1, -1);
    //    }

    //    const int normalTabsCount = ComboTabBar::normalTabsCount();
    //    const int maxTabWidth = comboTabBarPixelMetric(ComboTabBar::NormalTabMaximumWidth);

    //    if (availableWidth >= maxTabWidth * normalTabsCount) {
    //        m_normalTabWidth = maxTabWidth;
    //        size.setWidth(m_normalTabWidth);
    //    } else if (normalTabsCount > 0) {
    //        const int minActiveTabWidth = comboTabBarPixelMetric(ComboTabBar::ActiveTabMinimumWidth);

    //        int maxWidthForTab = availableWidth / normalTabsCount;
    //        int realTabWidth = maxWidthForTab;
    //        bool adjustingActiveTab = false;

    //        if (realTabWidth < minActiveTabWidth) {
    //            maxWidthForTab = normalTabsCount > 1 ? (availableWidth - minActiveTabWidth) / (normalTabsCount - 1) : 0;
    //            realTabWidth = minActiveTabWidth;
    //            adjustingActiveTab = true;
    //        }

    //        bool tryAdjusting = availableWidth >= minTabWidth * normalTabsCount;

    //        if (m_showCloseOnInactive != 1 && tabsClosable() && availableWidth < (minTabWidth + 25) * normalTabsCount) {
    //            // Hiding close buttons to save some space
    //            tabBar->setTabsClosable(false);
    //            tabBar->showCloseButton(currentIndex());
    //        }
    //        if (m_showCloseOnInactive == 1) {
    //            // Always showing close buttons
    //            tabBar->setTabsClosable(true);
    //            tabBar->showCloseButton(currentIndex());
    //        }

    //        if (tryAdjusting) {
    //            m_normalTabWidth = maxWidthForTab;

    //            // Fill any empty space (we've got from rounding) with active tab
    //            if (index == mainTabBarCurrentIndex()) {
    //                if (adjustingActiveTab) {
    //                    m_activeTabWidth = (availableWidth - minActiveTabWidth
    //                        - maxWidthForTab * (normalTabsCount - 1)) + realTabWidth;
    //                } else {
    //                    m_activeTabWidth = (availableWidth - maxWidthForTab * normalTabsCount) + maxWidthForTab;
    //                }
    //                size.setWidth(m_activeTabWidth);
    //            } else {
    //                size.setWidth(m_normalTabWidth);
    //            }
    //        }
    //    }

    //    // Restore close buttons according to preferences
    //    if (m_showCloseOnInactive != 2 && !tabsClosable() && availableWidth >= (minTabWidth + 25) * normalTabsCount) {
    //        tabBar->setTabsClosable(true);

    //        // Hide close buttons on pinned tabs
    //        for (int i = 0; i < count(); ++i) {
    //            tabBar->updatePinnedTabCloseButton(i);
    //        }
    //    }
    //}

    //if (index == count() - 1) {
    //    WebTab* lastMainActiveTab = qobject_cast<WebTab*>(m_tabWidget->widget(mainTabBarCurrentIndex()));
    //    int xForAddTabButton = cornerWidth(Qt::TopLeftCorner) + pinTabBarWidth() + normalTabsCount() * m_normalTabWidth;

    //    if (lastMainActiveTab && m_activeTabWidth > m_normalTabWidth) {
    //        xForAddTabButton += m_activeTabWidth - m_normalTabWidth;
    //    }

    //    if (QApplication::layoutDirection() == Qt::RightToLeft) {
    //        xForAddTabButton = width() - xForAddTabButton;
    //    }

    //    emit tabBar->moveAddTabButton(xForAddTabButton);
    //}

    //return size;

    return QSize(-1, -1);
}

int MYTabBar::comboTabBarPixelMetric(ComboTabBar::SizeType sizeType) const
{
    switch (sizeType) {
    case ComboTabBar::PinnedTabWidth:
        return tabMetrics()->pinnedWidth() > 0 ? tabMetrics()->pinnedWidth() : 32;

    case ComboTabBar::ActiveTabMinimumWidth:
        return tabMetrics()->activeMinWidth();

    case ComboTabBar::NormalTabMinimumWidth:
        return tabMetrics()->normalMinWidth();

    case ComboTabBar::OverflowedTabWidth:
        return tabMetrics()->overflowedWidth();

    case ComboTabBar::NormalTabMaximumWidth:
        return tabMetrics()->normalMaxWidth();

        /*  case ComboTabBar::ExtraReservedWidth:
              return m_tabWidget->extraReservedWidth();*/

    default:
        break;
    }

    return -1;
}

QLabel* MYTabBar::webTab(int index) const
{
    //if (index == -1) {
    //    return qobject_cast<WebTab*>(m_tabWidget->widget(currentIndex()));
    //}
    //return qobject_cast<WebTab*>(m_tabWidget->widget(index));
    return nullptr;
}

void MYTabBar::showCloseButton(int index)
{
    if (!validIndex(index)) {
        return;
    }

    /*  WebTab* webTab = qobject_cast<WebTab*>(m_tabWidget->widget(index));
      QAbstractButton* button = qobject_cast<QAbstractButton*>(tabButton(index, closeButtonPosition()));

      if (button || (webTab && webTab->isPinned())) {
          return;
      }

      insertCloseButton(index);*/
}

void MYTabBar::contextMenuEvent(QContextMenuEvent* event)
{
    if (isDragInProgress()) {
        return;
    }

    int index = tabAt(event->pos());

    //TabContextMenu menu(index, m_window);

    //// Prevent choosing first option with double rightclick
    //const QPoint pos = event->globalPos();
    //QPoint p(pos.x(), pos.y() + 1);
    //menu.exec(p);
}

void MYTabBar::hideCloseButton(int index)
{
    if (!validIndex(index) || tabsClosable()) {
        return;
    }

    MYCloseButton* button = qobject_cast<MYCloseButton*>(tabButton(index, closeButtonPosition()));
    if (!button) {
        return;
    }

    setTabButton(index, closeButtonPosition(), 0);
    button->deleteLater();
}

void MYTabBar::updatePinnedTabCloseButton(int index)
{
    if (!validIndex(index)) {
        return;
    }

    /*WebTab* webTab = qobject_cast<WebTab*>(m_tabWidget->widget(index));
    QAbstractButton* button = qobject_cast<QAbstractButton*>(tabButton(index, closeButtonPosition()));

    bool pinned = webTab && webTab->isPinned();

    if (pinned) {
        if (button) {
            button->hide();
        }
    } else {
        if (button) {
            button->show();
        } else {
            showCloseButton(index);
        }
    }*/
}

void MYTabBar::closeTabFromButton()
{
    QWidget* button = qobject_cast<QWidget*>(sender());

    int tabToClose = -1;

    for (int i = 0; i < count(); ++i) {
        if (tabButton(i, closeButtonPosition()) == button) {
            tabToClose = i;
            break;
        }
    }

    //if (tabToClose != -1) {
    //    m_tabWidget->requestCloseTab(tabToClose);
    //}
}

void MYTabBar::currentTabChanged(int index)
{
    if (!validIndex(index)) {
        return;
    }

    // Don't hide close buttons when dragging tabs
    if (m_dragStartPosition.isNull()) {
        showCloseButton(index);
        if (m_lastTab) {
            //hideCloseButton(m_lastTab->tabIndex());
        }
        QTimer::singleShot(100, this, [this]() { ensureVisible(); });
    }

    m_lastTab = webTab(index);
    //m_tabWidget->currentTabChanged(index);
}

void MYTabBar::setTabText(int index, const QString &text)
{
    QString tabText = text;

    // Avoid Alt+letter shortcuts
    tabText.replace(QLatin1Char('&'), QLatin1String("&&"));

    //if (QLabel* tab = webTab(index)) {
    //    if (tab->isPinned()) {
    //        tabText.clear();
    //    }
    //}

    setTabToolTip(index, text);
    ComboTabBar::setTabText(index, tabText);
}

void MYTabBar::tabInserted(int index)
{
    Q_UNUSED(index)

        // Initialize pinned tab metrics
        if (tabMetrics()->pinnedWidth() == -1) {
            QTimer::singleShot(0, this, [this]() {
                if (tabMetrics()->pinnedWidth() != -1) {
                    return;
                }
                QWidget *w = tabButton(0, iconButtonPosition());
                if (w && w->parentWidget()) {
                    const QRect wg = w->parentWidget()->geometry();
                    const QRect wr = QStyle::visualRect(layoutDirection(), wg, w->geometry());
                    tabMetrics()->setPinnedWidth(iconButtonSize().width() + wr.x() * 2);
                    setUpLayout();
                }
            });
        }

    setVisible(!(count() <= 1 && m_hideTabBarWithOneTab));
}

void MYTabBar::tabRemoved(int index)
{
    Q_UNUSED(index)

        showCloseButton(currentIndex());
    setVisible(!(count() <= 1 && m_hideTabBarWithOneTab));

    // Make sure to move add tab button to correct position when there are no normal tabs
    if (normalTabsCount() == 0) {
        int xForAddTabButton = cornerWidth(Qt::TopLeftCorner) + pinTabBarWidth();
        if (QApplication::layoutDirection() == Qt::RightToLeft)
            xForAddTabButton = width() - xForAddTabButton;
        emit moveAddTabButton(xForAddTabButton);
    }
}

void MYTabBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    //if (mApp->plugins()->processMouseDoubleClick(Qz::ON_TabBar, this, event)) {
    //    return;
    //}

    //if (event->buttons() == Qt::LeftButton && emptyArea(event->pos())) {
    //    m_tabWidget->addView(QUrl(), Qz::NT_SelectedTabAtTheEnd, true);
    //    return;
    //}

    ComboTabBar::mouseDoubleClickEvent(event);
}

void MYTabBar::mousePressEvent(QMouseEvent* event)
{
    ComboTabBar::mousePressEvent(event);

    //if (mApp->plugins()->processMousePress(Qz::ON_TabBar, this, event)) {
    //    return;
    //}

    if (event->buttons() == Qt::LeftButton && !emptyArea(event->pos())) {
        m_dragStartPosition = event->pos();
    } else {
        m_dragStartPosition = QPoint();
    }
}

void MYTabBar::mouseMoveEvent(QMouseEvent* event)
{
    ComboTabBar::mouseMoveEvent(event);

    /*if (mApp->plugins()->processMouseMove(Qz::ON_TabBar, this, event)) {
        return;
    }

    if (count() == 1 && mApp->windowCount() == 1) {
        return;
    }

    if (!m_dragStartPosition.isNull()) {
        int offset = 0;
        const int eventY = event->pos().y();
        if (eventY < 0) {
            offset = qAbs(eventY);
        } else if (eventY > height()) {
            offset = eventY - height();
        }
        if (offset > QApplication::startDragDistance() * 3) {
            const QPoint global = mapToGlobal(m_dragStartPosition);
            QWidget *w = QApplication::widgetAt(global);
            if (w) {
                QMouseEvent mouse(QEvent::MouseButtonRelease, w->mapFromGlobal(global), Qt::LeftButton, Qt::LeftButton, event->modifiers());
                QApplication::sendEvent(w, &mouse);
            }
            QDrag *drag = new QDrag(this);
            QMimeData *mime = new QMimeData;
            mime->setData(MIMETYPE, QByteArray());
            drag->setMimeData(mime);
            drag->setPixmap(tabPixmap(currentIndex()));
            if (drag->exec() == Qt::IgnoreAction) {
                m_tabWidget->detachTab(currentIndex());
            }
            return;
        }
    }*/
}

void MYTabBar::mouseReleaseEvent(QMouseEvent* event)
{
    ComboTabBar::mouseReleaseEvent(event);

    m_dragStartPosition = QPoint();

    //if (mApp->plugins()->processMouseRelease(Qz::ON_TabBar, this, event)) {
    //    return;
    //}

    //if (!rect().contains(event->pos())) {
    //    ComboTabBar::mouseReleaseEvent(event);
    //    return;
    //}

    //if (event->button() == Qt::MiddleButton) {
    //    if (emptyArea(event->pos())) {
    //        m_tabWidget->addView(QUrl(), Qz::NT_SelectedTabAtTheEnd, true);
    //        return;
    //    }

    //    int id = tabAt(event->pos());
    //    if (id != -1) {
    //        m_tabWidget->requestCloseTab(id);
    //        return;
    //    }
    //}
}

void MYTabBar::wheelEvent(QWheelEvent* event)
{
    //if (mApp->plugins()->processWheelEvent(Qz::ON_TabBar, this, event)) {
    //    return;
    //}

    ComboTabBar::wheelEvent(event);
}

enum TabDropAction {
    NoAction,
    SelectTab,
    PrependTab,
    AppendTab
};

static TabDropAction tabDropAction(const QPoint &pos, const QRect &tabRect, bool allowSelect)
{
    if (!tabRect.contains(pos)) {
        return NoAction;
    }

    const QPoint c = tabRect.center();
    const QSize csize = QSize(tabRect.width() * 0.7, tabRect.height() * 0.7);
    const QRect center(c.x() - csize.width() / 2, c.y() - csize.height() / 2, csize.width(), csize.height());

    if (allowSelect && center.contains(pos)) {
        return SelectTab;
    } else if (pos.x() < c.x()) {
        return PrependTab;
    } else {
        return AppendTab;
    }
}

void MYTabBar::dragEnterEvent(QDragEnterEvent* event)
{
    const QMimeData* mime = event->mimeData();

    if (mime->hasText() || mime->hasUrls() || (mime->hasFormat(MIMETYPE) && event->source())) {
        event->acceptProposedAction();
        return;
    }

    ComboTabBar::dragEnterEvent(event);
}

void MYTabBar::dragMoveEvent(QDragMoveEvent *event)
{
    const int index = tabAt(event->pos());
    const QMimeData* mime = event->mimeData();

    if (index == -1) {
        ComboTabBar::dragMoveEvent(event);
        return;
    }

    switch (tabDropAction(event->pos(), tabRect(index), !mime->hasFormat(MIMETYPE))) {
    case PrependTab:
        showDropIndicator(index, BeforeTab);
        break;
    case AppendTab:
        showDropIndicator(index, AfterTab);
        break;
    default:
        clearDropIndicator();
        break;
    }
}

void MYTabBar::dragLeaveEvent(QDragLeaveEvent *event)
{
    clearDropIndicator();

    ComboTabBar::dragLeaveEvent(event);
}

void MYTabBar::dropEvent(QDropEvent* event)
{
    clearDropIndicator();

    const QMimeData* mime = event->mimeData();

    if (!mime->hasText() && !mime->hasUrls() && !mime->hasFormat(MIMETYPE)) {
        ComboTabBar::dropEvent(event);
        return;
    }

    event->acceptProposedAction();

    MYTabBar *sourceTabBar = qobject_cast<MYTabBar*>(event->source());

    /*int index = tabAt(event->pos());
    if (index == -1) {
        if (mime->hasUrls()) {
            foreach(const QUrl &url, mime->urls()) {
                m_tabWidget->addView(url, Qz::NT_SelectedTabAtTheEnd);
            }
        } else if (mime->hasText()) {
            m_tabWidget->addView(mApp->searchEnginesManager()->searchResult(mime->text()), Qz::NT_SelectedNewEmptyTab);
        } else if (mime->hasFormat(MIMETYPE) && sourceTabBar) {
            WebTab *tab = sourceTabBar->webTab();
            if (tab) {
                sourceTabBar->m_tabWidget->detachTab(tab);
                tab->setPinned(false);
                m_tabWidget->addView(tab, Qz::NT_SelectedTab);
            }
        }
    } else {
        LoadRequest req;
        WebTab* tab = m_tabWidget->webTab(index);
        TabDropAction action = tabDropAction(event->pos(), tabRect(index), !mime->hasFormat(MIMETYPE));
        if (mime->hasUrls()) {
            req = mime->urls().at(0);
        } else if (mime->hasText()) {
            req = mApp->searchEnginesManager()->searchResult(mime->text());
        }
        if (action == SelectTab) {
            if (req.isValid()) {
                tab->load(req);
            }
        } else if (action == PrependTab || action == AppendTab) {
            const int newIndex = action == PrependTab ? index : index + 1;
            if (req.isValid()) {
                m_tabWidget->addView(req, QString(), Qz::NT_SelectedNewEmptyTab, false, newIndex, index < pinnedTabsCount());
            } else if (mime->hasFormat(MIMETYPE) && sourceTabBar) {
                WebTab *tab = sourceTabBar->webTab();
                if (tab) {
                    if (sourceTabBar == this) {
                        tab->moveTab(newIndex > tab->tabIndex() ? newIndex - 1 : newIndex);
                    } else {
                        sourceTabBar->m_tabWidget->detachTab(tab);
                        tab->setPinned(index < pinnedTabsCount());
                        m_tabWidget->insertView(newIndex, tab, Qz::NT_SelectedTab);
                    }
                }
            }
        }
    }*/
}

