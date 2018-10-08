#ifndef tabbar_h__
#define tabbar_h__

#include "ctrl_common.h"
#include "wheel.h"
#include "tabicon.h"
#include "toolbutton.h"
#include "ComboTabBar.h"
#include <QTabBar>
#include <QScrollBar>
#include <QAbstractButton>
#include <QEasingCurve>
#include <QStyleOption>
#include <QQueue>
#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QStylePainter>
#include <QToolButton>
#include <QTimer>
#include <QPointer>
#include <QLabel>

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif



class BrowserWindow;
class TabWidget;
class WebTab;

class MYTabBar : public ComboTabBar
{
    Q_OBJECT
public:
    explicit MYTabBar(BrowserWindow* window, TabWidget* tabWidget);

    void loadSettings();

    TabWidget* tabWidget() const;
    void setVisible(bool visible);
    void setForceHidden(bool hidden);

    void setTabText(int index, const QString &text);

    void wheelEvent(QWheelEvent* event);

Q_SIGNALS:
    void moveAddTabButton(int posX);

    private Q_SLOTS:
    void currentTabChanged(int index);
    void overflowChanged(bool overflowed);
    void closeTabFromButton();

private:
    inline bool validIndex(int index) const { return index >= 0 && index < count(); }

    void tabInserted(int index);
    void tabRemoved(int index);

    void hideCloseButton(int index);
    void showCloseButton(int index);
    void updatePinnedTabCloseButton(int index);

    void contextMenuEvent(QContextMenuEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent* event);

    QSize tabSizeHint(int index, bool fast) const;
    int comboTabBarPixelMetric(ComboTabBar::SizeType sizeType) const;
    QLabel* webTab(int index = -1) const;

    BrowserWindow* m_window;
    TabWidget* m_tabWidget;

    bool m_hideTabBarWithOneTab;

    int m_showCloseOnInactive;

    mutable int m_normalTabWidth;
    mutable int m_activeTabWidth;

    QPoint m_dragStartPosition;

    bool m_forceHidden;
    QPointer<QLabel> m_lastTab;
};

#endif // tabbar_h__
