#ifndef tabwidget_h__
#define tabwidget_h__

#include <QTabWidget>

class TabBar;
class QLabel;
class WebView;

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget* parent = nullptr);

public:
    QLabel* currentWebView() const;
    QLabel* webView(int index) const;
    int webViewIndex(QLabel *webView) const;

    TabBar* tabBar();

signals:
    void tabsChanged();
    void lastTabClosed();

public slots:
    void loadUrlInCurrentTab(const QUrl &url);
    QLabel* newTab(bool makeCurrent = true);
    void cloneTab(int index = -1);
    void closeTab(int index = -1);
    void closeOtherTabs(int index);
    void reloadTab(int index = -1);
    void reloadAllTabs();
    void nextTab();
    void previousTab();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);
    QRect addTabButtonRect();

private slots:
    void currentChanged(int index);
    void moveTab(int fromIndex, int toIndex);

private:
    TabBar* m_tabBar;
    QPixmap mAddTabIcon;

    static const int sRecentlyClosedTabsSize = 10;
};

#endif // tabwidget_h__
