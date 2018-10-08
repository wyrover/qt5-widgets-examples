#ifndef tabbar_h__
#define tabbar_h__

#include <QTabBar>
#include <QPoint>

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(QWidget* parent = nullptr);


signals:
    void newTab();
    void cloneTab(int index);
    void closeTab(int index);
    void closeOtherTabs(int index);
    void reloadTab(int index);
    void reloadAllTabs();
    void tabMoveRequested(int fromIndex, int toIndex);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);

private slots:
    void selectTabAction();
    void cloneTab();
    void closeTab();
    void closeOtherTabs();
    void reloadTab();
    void contextMenuRequested(const QPoint &position);

private:
    QList<QShortcut*> m_tabShortcuts;
    QPoint m_dragStartPos;
    int m_dragCurrentIndex;

    friend class TabWidget;
};

#endif // tabbar_h__
