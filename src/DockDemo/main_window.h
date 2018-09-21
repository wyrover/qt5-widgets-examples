#pragma once

#include <QMainWindow>
#include <QList>


class ConfigManager;
class ConfigManagerDialog;
class QSettings;
class DockHost;
class QDockWidget;


namespace Ui
{
class MainWindow;
}


class MainWindow :
    public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event);
    void changeEvent(QEvent* event);

private Q_SLOTS:
    void onConfigLoad();
    void onConfigSave();
    void onConfigError(const QString& error);
    void onActionAbout();
    void onActionLockDocks(bool checked);
    void onActionConfigManager();
    void onMenuConfigAboutToShow();
    void onMenuConfigTriggered();
    void onActionNewWindow();
    void onActionTest();
    void onThemeError(const QString& error);
    void onThemeLoaded();
    void onActionLoadTheme();

private:
    Ui::MainWindow *ui;

private:
    QAction*    actionNewFixed;
    QAction*    actionNewSized;
    QAction*    actionExit;
    QAction*    actionAbout;
    QAction*    actionLockDocks;
    QAction*    actionTabsToDocks;
    QAction*    actionConfigManager;
    QAction*    actionNewWindow;
    QAction*    actionTest;
    QMenu*      menuView;
    QMenu*      menuConfig;
    QMenu*      menuTheme;
    QList<QAction*> listThemeActions;
    ConfigManagerDialog*    configDialog;
    DockHost*   dockHost;

private:
    void initActions();
    void initMenus();
    void initDocks();
    QDockWidget* createDock(QWidget* widget, const QString& title);
    void moveToDock(QWidget* widget, const QString& title, Qt::DockWidgetArea area);
    void createDocks();

private:
    bool confirmApExit();
};
