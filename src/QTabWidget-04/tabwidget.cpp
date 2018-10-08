#include "tabwidget.h"
#include "tabbar.h"
#include <QToolButton>
#include <QVariant>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QClipboard>
#include <QPainter>
#include <QDebug>

// https://github.com/hxpe/qt-kso-484/blob/d627e61c0e586715a502b4e7baa78b3f6399dab1/demos/browser/tabwidget.cpp

TabWidget::TabWidget(QWidget* parent /*= nullptr*/)
    : QTabWidget(parent)
    , m_tabBar(new TabBar(this))
{
    mAddTabIcon = QPixmap(":/images/toolbar/plusBlack.png");
    setElideMode(Qt::ElideRight);
    setTabBar(m_tabBar);
    setTabPosition(QTabWidget::North);
    setDocumentMode(true);

    connect(m_tabBar, SIGNAL(newTab()), this, SLOT(newTab()));
    connect(m_tabBar, SIGNAL(closeTab(int)), this, SLOT(closeTab(int)));
    connect(m_tabBar, SIGNAL(cloneTab(int)), this, SLOT(cloneTab(int)));
    connect(m_tabBar, SIGNAL(closeOtherTabs(int)), this, SLOT(closeOtherTabs(int)));
    connect(m_tabBar, SIGNAL(reloadTab(int)), this, SLOT(reloadTab(int)));
    connect(m_tabBar, SIGNAL(reloadAllTabs()), this, SLOT(reloadAllTabs()));
    connect(m_tabBar, &TabBar::tabMoveRequested, this, &TabWidget::moveTab);

    QToolButton *addTabButton = new QToolButton(this);
    //addTabButton->setDefaultAction(m_newTabAction);
    addTabButton->setAutoRaise(true);
    addTabButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    setCornerWidget(addTabButton, Qt::TopLeftCorner);


    QToolButton *closeTabButton = new QToolButton(this);
    //closeTabButton->setDefaultAction(m_closeTabAction);
    closeTabButton->setAutoRaise(true);
    closeTabButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    setCornerWidget(closeTabButton, Qt::TopRightCorner);
}

QLabel* TabWidget::currentWebView() const
{
    return webView(currentIndex());
}

QLabel* TabWidget::webView(int index) const
{
    QWidget *widget = this->widget(index);
    if (QLabel *webView = qobject_cast<QLabel*>(widget)) {
        return webView;
    } else {
        // optimization to delay creating the first webview
        if (count() == 1) {
            TabWidget *that = const_cast<TabWidget*>(this);
            that->setUpdatesEnabled(false);
            that->newTab();
            that->closeTab(0);
            that->setUpdatesEnabled(true);
            return currentWebView();
        }
    }
    return 0;
}

int TabWidget::webViewIndex(QLabel *webView) const
{
    int index = indexOf(webView);
    return index;
}

TabBar* TabWidget::tabBar() 
{
    return m_tabBar;
}

void TabWidget::loadUrlInCurrentTab(const QUrl &url)
{
    QLabel *webView = currentWebView();
    if (webView) {
        //webView->load(url);
        webView->setFocus();
    }
}

QLabel* TabWidget::newTab(bool makeCurrent /*= true*/)
{
    QLabel* ret = new QLabel(tr("test"));
    addTab(ret, "test");
    return ret;
}

void TabWidget::cloneTab(int index /*= -1*/)
{
    if (index < 0)
        index = currentIndex();
    if (index < 0 || index >= count())
        return;
    QLabel *tab = newTab(false);
    //tab->setUrl(webView(index)->url());
}

void TabWidget::closeTab(int index /*= -1*/)
{
    if (index < 0)
        index = currentIndex();
    if (index < 0 || index >= count())
        return;


    
    QWidget *webView = widget(index);
    removeTab(index);
    webView->deleteLater();
    emit tabsChanged();
    if (count() > 0)
        currentWebView()->setFocus();
    if (count() == 0)
        emit lastTabClosed();
}

void TabWidget::closeOtherTabs(int index)
{
    if (-1 == index)
        return;
    for (int i = count() - 1; i > index; --i)
        closeTab(i);
    for (int i = index - 1; i >= 0; --i)
        closeTab(i);
}

void TabWidget::reloadTab(int index /*= -1*/)
{
    if (index < 0)
        index = currentIndex();
    if (index < 0 || index >= count())
        return;

    QWidget *widget = this->widget(index);
    if (QLabel *tab = qobject_cast<QLabel*>(widget)) {
        //tab->reload();
    }
}

void TabWidget::reloadAllTabs()
{
    for (int i = 0; i < count(); ++i) {
        QWidget *tabWidget = widget(i);
        if (QLabel *tab = qobject_cast<QLabel*>(tabWidget)) {
            //tab->reload();
        }
    }
}

void TabWidget::nextTab()
{
    int next = currentIndex() + 1;
    if (next == count())
        next = 0;
    setCurrentIndex(next);
}

void TabWidget::previousTab()
{
    int next = currentIndex() - 1;
    if (next < 0)
        next = count() - 1;
    setCurrentIndex(next);
}

void TabWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (!childAt(event->pos())
        // Remove the line below when QTabWidget does not have a one pixel frame
        && event->pos().y() < (tabBar()->y() + tabBar()->height())) {
        newTab();
        return;
    }
    QTabWidget::mouseDoubleClickEvent(event);
}

void TabWidget::contextMenuEvent(QContextMenuEvent *event)
{
    if (!childAt(event->pos())) {
        m_tabBar->contextMenuRequested(event->pos());
        return;
    }
    QTabWidget::contextMenuEvent(event);
}

void TabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QRect addTabRect = addTabButtonRect();

    if (addTabRect.contains(event->pos())) {
        newTab();
    } else if (event->button() == Qt::MidButton && !childAt(event->pos())
        // Remove the line below when QTabWidget does not have a one pixel frame
        && event->pos().y() < (tabBar()->y() + tabBar()->height())) {
        QUrl url(QApplication::clipboard()->text(QClipboard::Selection));
        if (!url.isEmpty() && url.isValid() && !url.scheme().isEmpty()) {
            QLabel *webView = newTab();
            //webView->setUrl(url);
        }
    }
}

void TabWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    // all this is in synch with CSS QTabBar ...
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, 1));
    linearGrad.setColorAt(0, QColor("#d3d3d3"));
    linearGrad.setColorAt(1, QColor("#dddddd"));
    painter.setBrush(linearGrad);

    QRect r = addTabButtonRect();

    painter.setPen(QColor("#888888"));
    painter.drawRoundedRect(r, 3, 3);

    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect(r.x(), r.y() + r.height() / 2, r.width() + 1, r.height() / 2 + 1));

    painter.setPen(QColor("#888888"));
    painter.drawLine(r.x(), r.y() + r.height() / 2, r.x(), r.bottom());
    painter.drawLine(r.right() + 1, r.y() + r.height() / 2, r.right() + 1, r.bottom());

    if (tabPosition() == QTabWidget::South) {
        QPen pen = painter.pen();
        pen.setColor(QColor("#b3b3b3"));
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(0, r.bottom() + 2, width(), r.bottom() + 2);
    }

    QPointF topLeft = r.center() - QPointF(mAddTabIcon.width() / 2, mAddTabIcon.height() / 2);
    painter.drawPixmap(topLeft, mAddTabIcon);

    painter.end();

    QTabWidget::paintEvent(event);
}

QRect TabWidget::addTabButtonRect()
{
    QRect lastTabRect = tabBar()->tabRect(tabBar()->count() - 1);
    int x = lastTabRect.topRight().x();
    int y;

    if (tabPosition() == QTabWidget::North)
        y = lastTabRect.topRight().y();
    else if (tabPosition() == QTabWidget::South)
        y = geometry().height() - lastTabRect.height();
    else
        qDebug() << "WBTabWidget::addTabButtonRect() - unsupported tab posion";

    // all this is in synch with CSS QTabBar ...
    QRect r(x + 3, y + 6, 25, lastTabRect.height() - 8);

    return r;
}

void TabWidget::currentChanged(int index)
{
    QLabel *webView = this->webView(index);
    if (!webView)
        return;
}

void TabWidget::moveTab(int fromIndex, int toIndex)
{
    disconnect(this, &TabWidget::currentChanged,
        this, &TabWidget::currentChanged);

    QWidget *tabWidget = widget(fromIndex);
    QIcon icon = tabIcon(fromIndex);
    QString text = tabText(fromIndex);
    QVariant data = m_tabBar->tabData(fromIndex);
    removeTab(fromIndex);
    insertTab(toIndex, tabWidget, icon, text);
    m_tabBar->setTabData(toIndex, data);
    connect(this, &TabWidget::currentChanged,
        this, &TabWidget::currentChanged);
    setCurrentIndex(toIndex);
}
