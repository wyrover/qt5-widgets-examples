#include "tabbar.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QMenu>
#include <QShortcut>

TabBar::TabBar(QWidget* parent /*= nullptr*/)
    : QTabBar(parent)
{
    setContextMenuPolicy(Qt::CustomContextMenu);    
    setAcceptDrops(true);
    setTabsClosable(true);
    setMovable(true);
    setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);

    QString ctrl = QLatin1String("Ctrl+%1");
    for (int i = 1; i <= 10; ++i) {
        int key = i;
        if (key == 10)
            key = 0;
        QShortcut *shortCut = new QShortcut(ctrl.arg(key), this);
        m_tabShortcuts.append(shortCut);
        connect(shortCut, SIGNAL(activated()), this, SLOT(selectTabAction()));
    }

    connect(this, &TabBar::customContextMenuRequested, this, &TabBar::contextMenuRequested);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SIGNAL(closeTab(int)));
}

void TabBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        m_dragStartPos = event->pos();
    QTabBar::mousePressEvent(event);
}

void TabBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        int diffX = event->pos().x() - m_dragStartPos.x();
        int diffY = event->pos().y() - m_dragStartPos.y();
        if ((event->pos() - m_dragStartPos).manhattanLength() > QApplication::startDragDistance()
            && diffX < 3 && diffX > -3
            && diffY < -10) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            QList<QUrl> urls;
            int index = tabAt(event->pos());
            QUrl url = tabData(index).toUrl();
            urls.append(url);
            mimeData->setUrls(urls);
            mimeData->setText(tabText(index));
            mimeData->setData(QLatin1String("action"), "tab-reordering");
            drag->setMimeData(mimeData);
            drag->exec();
        }
    }
    QTabBar::mouseMoveEvent(event);
}

void TabBar::dragEnterEvent(QDragEnterEvent* event)
{
    //const QMimeData *mimeData = event->mimeData();
    //QStringList formats = mimeData->formats();
    //if (formats.contains(QLatin1String("action"))
    //    && (mimeData->data(QLatin1String("action")) == "tab-reordering")) {
    //    event->acceptProposedAction();
    //}
    QTabBar::dragEnterEvent(event);
}

void TabBar::dropEvent(QDropEvent* event)
{
    //int fromIndex = tabAt(m_dragStartPos);
    //int toIndex = tabAt(event->pos());
    //if (fromIndex != toIndex) {
    //    emit tabMoveRequested(fromIndex, toIndex);
    //    event->acceptProposedAction();
    //}
    QTabBar::dropEvent(event);
}



void TabBar::selectTabAction()
{
    if (QShortcut *shortCut = qobject_cast<QShortcut*>(sender())) {
        int index = m_tabShortcuts.indexOf(shortCut);
        if (index == 0)
            index = 10;
        setCurrentIndex(index);
    }
}

void TabBar::cloneTab()
{
    if (QAction *action = qobject_cast<QAction*>(sender())) {
        int index = action->data().toInt();
        emit cloneTab(index);
    }
}



void TabBar::closeTab()
{
    if (QAction *action = qobject_cast<QAction*>(sender())) {
        int index = action->data().toInt();
        emit closeTab(index);
    }
}



void TabBar::closeOtherTabs()
{
    if (QAction *action = qobject_cast<QAction*>(sender())) {
        int index = action->data().toInt();
        emit closeOtherTabs(index);
    }
}



void TabBar::reloadTab()
{
    if (QAction *action = qobject_cast<QAction*>(sender())) {
        int index = action->data().toInt();
        emit reloadTab(index);
    }
}

void TabBar::contextMenuRequested(const QPoint &position)
{
    QMenu menu;
    menu.addAction(tr("New &Tab"), this, SIGNAL(newTab()), QKeySequence::AddTab);
    int index = tabAt(position);
    if (-1 != index) {
        QAction *action = menu.addAction(tr("Clone Tab"),
            this, SLOT(cloneTab()));
        action->setData(index);

        menu.addSeparator();

        action = menu.addAction(tr("&Close Tab"),
            this, SLOT(closeTab()), QKeySequence::Close);
        action->setData(index);

        action = menu.addAction(tr("Close &Other Tabs"),
            this, SLOT(closeOtherTabs()));
        action->setData(index);

        menu.addSeparator();

        action = menu.addAction(tr("Reload Tab"),
            this, SLOT(reloadTab()), QKeySequence::Refresh);
        action->setData(index);
    } else {
        menu.addSeparator();
    }
    menu.addAction(tr("Reload All Tabs"), this, SIGNAL(reloadAllTabs()));
    menu.exec(QCursor::pos());
}
