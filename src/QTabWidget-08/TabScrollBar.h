#ifndef TabScrollBar_h__
#define TabScrollBar_h__


#include <QScrollBar>
#include <QPropertyAnimation>
#include <QAbstractButton>
#include <QTabBar>

class QTabBar;
class QScrollArea;
class ToolButton;

class TabScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit TabScrollBar(QWidget* parent = 0);
    ~TabScrollBar();

    bool isScrolling() const;

    void animateToValue(int to, QEasingCurve::Type type = QEasingCurve::OutQuad);

private:
    QPropertyAnimation* m_animation;
};


class TabBarScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TabBarScrollWidget(QTabBar* tabBar, QWidget* parent = 0);

    QTabBar* tabBar();
    QScrollArea* scrollArea();
    TabScrollBar* scrollBar();

    void scrollByWheel(QWheelEvent* event);

    int scrollButtonsWidth() const;
    bool usesScrollButtons() const;
    void setUsesScrollButtons(bool useButtons);

    bool isOverflowed() const;
    int tabAt(const QPoint &pos) const;

    public Q_SLOTS:
    void ensureVisible(int index = -1, int xmargin = 132);
    void scrollToLeft(int n = 5, QEasingCurve::Type type = QEasingCurve::OutQuad);
    void scrollToRight(int n = 5, QEasingCurve::Type type = QEasingCurve::OutQuad);
    void scrollToLeftEdge();
    void scrollToRightEdge();
    void setUpLayout();

    private Q_SLOTS:
    void overFlowChanged(bool overflowed);
    void scrollStart();
    void updateScrollButtonsState();

private:
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

    QTabBar* m_tabBar;
    QScrollArea* m_scrollArea;
    TabScrollBar* m_scrollBar;
    ToolButton* m_rightScrollButton;
    ToolButton* m_leftScrollButton;
    bool m_usesScrollButtons;
    int m_totalDeltas;
};



#endif // TabScrollBar_h__
