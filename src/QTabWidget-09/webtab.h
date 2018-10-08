#ifndef webtab_h__
#define webtab_h__

#include <QWidget>
#include <QIcon>
#include <QUrl>

#include "qzcommon.h"

class QVBoxLayout;
class QSplitter;
class TabIcon;
class MyTabBar;


class WebTab : public QWidget
{
    Q_OBJECT
public:
    

    enum AddChildBehavior {
        AppendChild = 0,
        PrependChild
    };

    explicit WebTab(QWidget *parent = nullptr);

    //BrowserWindow *browserWindow() const;
    //TabbedWebView* webView() const;
    //LocationBar* locationBar() const;
    TabIcon* tabIcon() const;

    WebTab *parentTab() const;
    void setParentTab(WebTab *tab);
    void addChildTab(WebTab *tab, int index = -1);
    QVector<WebTab*> childTabs() const;

    QHash<QString, QVariant> sessionData() const;
    void setSessionData(const QString &key, const QVariant &value);

    QUrl url() const;
    QString title(bool allowEmpty = false) const;
    QIcon icon(bool allowNull = false) const;
    //QWebEngineHistory* history() const;
    int zoomLevel() const;
    void setZoomLevel(int level);

    void detach();
    //void attach(BrowserWindow* window);

    QByteArray historyData() const;

    void stop();
    void reload();
    //void load(const LoadRequest &request);
    void unload();
    bool isLoading() const;

    bool isPinned() const;
    void setPinned(bool state);
    void togglePinned();

    bool isMuted() const;
    bool isPlaying() const;
    void setMuted(bool muted);
    void toggleMuted();

    bool backgroundActivity() const;

    int tabIndex() const;

    bool isCurrentTab() const;
    void makeCurrentTab();
    void closeTab();
    void moveTab(int to);

    bool haveInspector() const;
    void showWebInspector(bool inspectElement = false);
    void toggleWebInspector();

    void showSearchToolBar(const QString &searchText = QString());

    bool isRestored() const;
    //void restoreTab(const SavedTab &tab);
    //void p_restoreTab(const SavedTab &tab);
    void p_restoreTab(const QUrl &url, const QByteArray &history, int zoomLevel);

    void tabActivated();

    static AddChildBehavior addChildBehavior();
    static void setAddChildBehavior(AddChildBehavior behavior);

    private Q_SLOTS:
    void showNotification(QWidget* notif);
    void loadFinished();

Q_SIGNALS:
    void titleChanged(const QString &title);
    void iconChanged(const QIcon &icon);
    void pinnedChanged(bool pinned);
    void restoredChanged(bool restored);
    void currentTabChanged(bool current);
    void loadingChanged(bool loading);
    void mutedChanged(bool muted);
    void playingChanged(bool playing);
    void backgroundActivityChanged(bool activity);
    void parentTabChanged(WebTab *tab);
    void childTabAdded(WebTab *tab, int index);
    void childTabRemoved(WebTab *tab, int index);

private:
    void titleWasChanged(const QString &title);
    void resizeEvent(QResizeEvent *event) override;
    void removeFromTabTree();

    QVBoxLayout* m_layout;
    QSplitter* m_splitter;

    //TabbedWebView* m_webView;
    //WebInspector* m_inspector;
    //LocationBar* m_locationBar;
    TabIcon* m_tabIcon;
    QWidget *m_notificationWidget;
    //BrowserWindow* m_window = nullptr;
    MyTabBar* m_tabBar = nullptr;

    WebTab *m_parentTab = nullptr;
    QVector<WebTab*> m_childTabs;
    QHash<QString, QVariant> m_sessionData;

    //SavedTab m_savedTab;
    bool m_isPinned = false;
    bool m_isCurrentTab = false;
};

#endif // webtab_h__
