#ifndef TabBarHelper_h__
#define TabBarHelper_h__

#include "ComboTabBar.h"
#include <QTabBar>
#include <QStyleOption>


class QScrollArea;
class QMovableTabWidget;

class TabBarHelper : public QTabBar
{
    Q_OBJECT
        Q_PROPERTY(int tabPadding READ tabPadding WRITE setTabPadding)
        Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)

public:
    explicit TabBarHelper(bool isPinnedTabBar, ComboTabBar* comboTabBar);

    int tabPadding() const;
    void setTabPadding(int padding);

    QColor baseColor() const;
    void setBaseColor(const QColor &color);

    void setTabButton(int index, QTabBar::ButtonPosition position, QWidget* widget);

    QSize tabSizeHint(int index) const;
    QSize baseClassTabSizeHint(int index) const;

    QRect draggedTabRect() const;
    QPixmap tabPixmap(int index) const;

    bool isActiveTabBar();
    void setActiveTabBar(bool activate);

    void removeTab(int index);

    void setScrollArea(QScrollArea* scrollArea);
    void useFastTabSizeHint(bool enabled);

    void showDropIndicator(int index, ComboTabBar::DropIndicatorPosition position);
    void clearDropIndicator();

    bool isDisplayedOnViewPort(int globalLeft, int globalRight);
    bool isDragInProgress() const;

    static void initStyleBaseOption(QStyleOptionTabBarBase* optTabBase, QTabBar* tabbar, QSize size);

    public Q_SLOTS:
    void setCurrentIndex(int index);

private:
    bool event(QEvent* ev);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);

    int dragOffset(QStyleOptionTab *option, int tabIndex) const;
    void initStyleOption(QStyleOptionTab* option, int tabIndex) const;

    ComboTabBar* m_comboTabBar;
    QScrollArea* m_scrollArea;

    int m_tabPadding = -1;
    QColor m_baseColor;
    int m_pressedIndex;
    bool m_dragInProgress;
    QPoint m_dragStartPosition;
    class QMovableTabWidget *m_movingTab = nullptr;
    bool m_activeTabBar;
    bool m_isPinnedTabBar;
    bool m_useFastTabSizeHint;
    int m_dropIndicatorIndex = -1;
    ComboTabBar::DropIndicatorPosition m_dropIndicatorPosition;
};

#endif // TabBarHelper_h__
