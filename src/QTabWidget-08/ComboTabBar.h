#ifndef ComboTabBar_h__
#define ComboTabBar_h__

#include "wheel.h"
#include <QWidget>
#include <QTabBar>


class TabBarHelper;
class QHBoxLayout;
class TabBarScrollWidget;

class QMovableTabWidget : public QWidget
{
public:
    QPixmap m_pixmap;
};


class ComboTabBar : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
        Q_PROPERTY(int count READ count)

public:
    enum SizeType {
        PinnedTabWidth,
        ActiveTabMinimumWidth,
        NormalTabMinimumWidth,
        NormalTabMaximumWidth,
        OverflowedTabWidth,
        ExtraReservedWidth
    };

    enum DropIndicatorPosition {
        BeforeTab,
        AfterTab
    };

    explicit ComboTabBar(QWidget* parent = 0);

    int addTab(const QString &text);
    int addTab(const QIcon &icon, const QString &text);

    int insertTab(int index, const QString &text);
    int insertTab(int index, const QIcon &icon, const QString &text, bool pinned = false);

    void removeTab(int index);
    void moveTab(int from, int to);

    bool isTabEnabled(int index) const;
    void setTabEnabled(int index, bool enabled);

    QColor tabTextColor(int index) const;
    void setTabTextColor(int index, const QColor &color);

    QRect tabRect(int index) const;
    QRect draggedTabRect() const;
    QPixmap tabPixmap(int index) const;

    // Returns tab index at pos, or -1
    int tabAt(const QPoint &pos) const;

    // Returns true if there is an empty area at pos
    // (returns false if there are buttons or other widgets on the pos)
    bool emptyArea(const QPoint &pos) const;

    int mainTabBarCurrentIndex() const;
    int currentIndex() const;
    int count() const;

    void setDrawBase(bool drawTheBase);
    bool drawBase() const;

    Qt::TextElideMode elideMode() const;
    void setElideMode(Qt::TextElideMode elide);

    QString tabText(int index) const;
    void setTabText(int index, const QString &text);

    void setTabToolTip(int index, const QString &tip);
    QString tabToolTip(int index) const;

    bool tabsClosable() const;
    void setTabsClosable(bool closable);

    void setTabButton(int index, QTabBar::ButtonPosition position, QWidget* widget);
    QWidget* tabButton(int index, QTabBar::ButtonPosition position) const;

    QTabBar::SelectionBehavior selectionBehaviorOnRemove() const;
    void setSelectionBehaviorOnRemove(QTabBar::SelectionBehavior behavior);

    bool expanding() const;
    void setExpanding(bool enabled);

    bool isMovable() const;
    void setMovable(bool movable);

    bool documentMode() const;
    void setDocumentMode(bool set);

    int pinnedTabsCount() const;
    int normalTabsCount() const;
    bool isPinned(int index) const;

    void setFocusPolicy(Qt::FocusPolicy policy);
    void setObjectName(const QString &name);
    void setMouseTracking(bool enable);

    void insertCloseButton(int index);
    void setCloseButtonsToolTip(const QString &tip);

    QTabBar::ButtonPosition iconButtonPosition() const;
    QTabBar::ButtonPosition closeButtonPosition() const;

    QSize iconButtonSize() const;
    QSize closeButtonSize() const;

    bool validIndex(int index) const;
    void setCurrentNextEnabledIndex(int offset);

    bool usesScrollButtons() const;
    void setUsesScrollButtons(bool useButtons);

    void showDropIndicator(int index, DropIndicatorPosition position);
    void clearDropIndicator();

    bool isDragInProgress() const;
    bool isScrollInProgress() const;
    bool isMainBarOverflowed() const;

    // Width of all widgets in the corner
    int cornerWidth(Qt::Corner corner) const;
    // Add widget to the left/right corner
    void addCornerWidget(QWidget* widget, Qt::Corner corner);

    // Duration of tab slide animation when releasing dragged tab
    static int slideAnimationDuration();

    public Q_SLOTS:
    void setUpLayout();
    void ensureVisible(int index = -1, int xmargin = -1);
    void setCurrentIndex(int index);

Q_SIGNALS:
    void overFlowChanged(bool overFlow);
    void currentChanged(int index);
    void tabCloseRequested(int index);
    void tabMoved(int from, int to);
    void scrollBarValueChanged(int value);

    private Q_SLOTS:
    void setMinimumWidths();
    void slotCurrentChanged(int index);
    void slotTabCloseRequested(int index);
    void slotTabMoved(int from, int to);
    void closeTabFromButton();
    void updateTabBars();
    void emitOverFlowChanged();

protected:
    int mainTabBarWidth() const;
    int pinTabBarWidth() const;

    bool event(QEvent *event);
    void wheelEvent(QWheelEvent* event);
    bool eventFilter(QObject* obj, QEvent* ev);
    void paintEvent(QPaintEvent* ev);

    virtual int comboTabBarPixelMetric(SizeType sizeType) const;
    virtual QSize tabSizeHint(int index, bool fast = false) const;
    virtual void tabInserted(int index);
    virtual void tabRemoved(int index);

private:
    TabBarHelper* mainTabBar() const;
    TabBarHelper* localTabBar(int index = -1) const;

    int toLocalIndex(int globalIndex) const;
    QRect mapFromLocalTabRect(const QRect &rect, QWidget *tabBar) const;
    void updatePinnedTabBarVisibility();

    QHBoxLayout* m_mainLayout;
    QHBoxLayout* m_leftLayout;
    QHBoxLayout* m_rightLayout;
    QWidget* m_leftContainer;
    QWidget* m_rightContainer;

    TabBarHelper* m_mainTabBar;
    TabBarHelper* m_pinnedTabBar;

    TabBarScrollWidget* m_mainTabBarWidget;
    TabBarScrollWidget* m_pinnedTabBarWidget;

    QString m_closeButtonsToolTip;
    bool m_mainBarOverFlowed;
    bool m_lastAppliedOverflow;
    bool m_usesScrollButtons;
    bool m_blockCurrentChangedSignal;

    WheelHelper m_wheelHelper;

    friend class TabBarHelper;
    friend class TabStackedWidget;
};

#endif // ComboTabBar_h__
