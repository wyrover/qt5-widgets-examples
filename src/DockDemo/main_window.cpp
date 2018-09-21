#include "main_window.h"
#include "ui_main_window.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QTabWidget>
#include <QDebug>
#include <QSettings>
#include <QDockWidget>

#include "info_widget.h"
#include "demo_widget.h"
#include "utils.h"
#include "dock/dock_host.h"
#include "config/config_manager.h"
#include "config/config_manager_dialog.h"
#include "theme/theme.h"
#include "theme/stylesheet_builder.h"
#include "about_dialog.h"


static int nextCount()
{
    static int count = 0;
    return ++count;
}

static const int ContentMargin = 4;


// --- MainWindow -------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    dockHost(new DockHost(parent)),
    ui(new Ui::MainWindow),
    configDialog(NULL)
{
    ui->setupUi(this);
    setContentsMargins(ContentMargin, ContentMargin, ContentMargin, ContentMargin);
    dockHost->setParent(this);
    initActions();
    initMenus();
    initDocks();
    setCentralWidget(NULL);
    createDocks();
    connect(theme(), &Theme::onError, this, &MainWindow::onThemeError);
    connect(theme(), &Theme::onLoaded, this, &MainWindow::onThemeLoaded);
    // !! change theme before restoring geometry !!
    QString theme = ::config->get("Theme", "dark").toString();
    ::theme()->load(theme);
    connect(config, &ConfigManager::onLoad, this, &MainWindow::onConfigLoad);
    connect(config, &ConfigManager::onSave, this, &MainWindow::onConfigSave);
    connect(config, &ConfigManager::onError, this, &MainWindow::onConfigError);
    ::config->loadDefault();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (confirmApExit()) {
        ::config->saveDefault();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange) {
        QWindowStateChangeEvent* stateChangeEvent = static_cast<QWindowStateChangeEvent*>(event);

        if (stateChangeEvent) {
            if (stateChangeEvent->oldState() == Qt::WindowMaximized && windowState() == Qt::WindowNoState) {
                adjustWidgetGeometry(this);
            }
        }
    }
}

void MainWindow::onConfigLoad()
{
    restoreGeometry(::config->get("Geometry").toByteArray());
    restoreState(::config->get("State").toByteArray());
}

void MainWindow::onConfigSave()
{
    ::config->set("Geometry", saveGeometry());
    ::config->set("State", saveState());
}

void MainWindow::onConfigError(const QString& error)
{
    qDebug() << error;
}

void MainWindow::onActionAbout()
{
    showAbout(this);
}

void MainWindow::onActionLockDocks(bool checked)
{
    dockHost->lockDocks(checked);
}

void MainWindow::onActionConfigManager()
{
    if (!configDialog) {
        configDialog = new ConfigManagerDialog(this);
    }

    configDialog->show();
}

void MainWindow::onMenuConfigAboutToShow()
{
    menuConfig->clear();
    menuConfig->addAction(actionConfigManager);
    menuConfig->addSeparator();

    Q_FOREACH (QString name, config->getConfigNames()) {
        QAction* action = menuConfig->addAction(name);
        QObject::connect(action, &QAction::triggered, this, &MainWindow::onMenuConfigTriggered);
    }
}

void MainWindow::onMenuConfigTriggered()
{
    QAction* action = static_cast<QAction*>(sender());
    QString name = action->text();
    config->load(name);
}

void MainWindow::onActionNewWindow()
{
    MainWindow* window = new MainWindow();
    window->show();
}

void MainWindow::onActionTest()
{
    //
}

void MainWindow::onThemeError(const QString& error)
{
    qDebug() << error;
}

void MainWindow::onThemeLoaded()
{
    // Check the current theme
    QString currentTheme = ::config->get("Theme", "dark").toString();

    Q_FOREACH (QAction* action, listThemeActions) {
        QString actionTheme = action->text();
        action->setChecked(currentTheme == actionTheme);
    }

    static const int BorderRadius = 4;
    static const int EditBorderRadius = 2;
    static const int BorderSize = 1;
}

void MainWindow::onActionLoadTheme()
{
    QAction* action = static_cast<QAction*>(sender());
    action->setChecked(!action->isChecked()); // revert to previous state, check it later, after theme changed
    QString name = action->text();
    ::config->set("Theme", name);
    ::config->sync();
    theme()->load(name);
}

void MainWindow::initActions()
{
    actionLockDocks = new QAction("&Lock Docks", this);
    actionLockDocks->setStatusTip("Lock Docks");
    actionLockDocks->setCheckable(true);
    connect(actionLockDocks, &QAction::triggered, this, &MainWindow::onActionLockDocks);
    actionNewWindow = new QAction("&New Window", this);
    actionNewWindow->setShortcut(QKeySequence::New);
    actionNewWindow->setStatusTip("Create New Main Window");
    connect(actionNewWindow, &QAction::triggered, this, &MainWindow::onActionNewWindow);
    actionTest = new QAction("&Test", this);
    connect(actionTest, &QAction::triggered, this, &MainWindow::onActionTest);
    actionExit = new QAction("E&xit", this);
    actionExit->setShortcut(QKeySequence::Quit);
    actionExit->setStatusTip("Exit the Application");
    connect(actionExit, &QAction::triggered, qApp, &QApplication::quit);
    actionAbout = new QAction("&About", this);
    actionAbout->setStatusTip("Show Information about the Application");
    connect(actionAbout, &QAction::triggered, this, &MainWindow::onActionAbout);
    actionConfigManager = new QAction("&Save...", this);
    actionConfigManager->setStatusTip("Open Config Manager");
    connect(actionConfigManager, &QAction::triggered, this, &MainWindow::onActionConfigManager);
}

void MainWindow::initMenus()
{
    QMenu* menuFile = menuBar()->addMenu("&File");
    menuFile->addAction(actionTest);
    menuFile->addSeparator();
    menuFile->addAction(actionNewWindow);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuView = menuBar()->addMenu("&View");
    menuView->addAction(actionLockDocks);
    menuView->addSeparator();
    menuConfig = menuBar()->addMenu("&Config");
    connect(menuConfig, &QMenu::aboutToShow, this, &MainWindow::onMenuConfigAboutToShow);
    menuTheme = menuBar()->addMenu("&Theme");

    Q_FOREACH (QString name, theme()->getThemeNames()) {
        QAction* action = new QAction(name, this);
        action->setStatusTip("Load theme " + name);
        action->setCheckable(true);
        connect(action, &QAction::triggered, this, &MainWindow::onActionLoadTheme);
        listThemeActions << action;
        menuTheme->addAction(action);
    }

    QMenu* menuHelp = menuBar()->addMenu("&Help");
    menuHelp->addAction(actionAbout);
}

void MainWindow::initDocks()
{
    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::North);
    setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks);
}

QDockWidget* MainWindow::createDock(QWidget* widget, const QString& title)
{
    widget->setProperty("IsDockable", true);
    QDockWidget* dock = dockHost->createDock(this, widget, title);
    menuView->addAction(dock->toggleViewAction());
    return dock;
}

void MainWindow::moveToDock(QWidget* widget, const QString& title, Qt::DockWidgetArea area)
{
    QDockWidget* dock = createDock(widget, title);
    addDockWidget(area, dock);
}

void MainWindow::createDocks()
{
    QWidget* widget1 = new InfoWidget(this);
    widget1->setObjectName("info1");
    QWidget* widget2 = new InfoWidget(this);
    widget2->setObjectName("info2");
    QWidget* widget3 = new InfoWidget(this);
    widget3->setObjectName("info3");
    QWidget* widget4 = new InfoWidget(this);
    widget4->setObjectName("info4");
    QDockWidget* dock1 = createDock(widget1, "Info 1 Widget");
    QDockWidget* dock2 = createDock(widget2, "Info 2 Widget");
    QDockWidget* dock3 = createDock(widget3, "Info 3 Widget");
    QDockWidget* dock4 = createDock(widget4, "Info 4 Widget");
    addDockWidget(Qt::BottomDockWidgetArea, dock1);
    splitDockWidget(dock1, dock2, Qt::Horizontal);
    splitDockWidget(dock1, dock3, Qt::Vertical);
    splitDockWidget(dock2, dock4, Qt::Vertical);
    {
        QWidget* widget1 = new DemoWidget(this);
        widget1->setObjectName("demo1");
        QWidget* widget2 = new DemoWidget(this);
        widget2->setObjectName("demo2");
        QDockWidget* dock1 = createDock(widget1, "Big 1 Widget with long Title");
        QDockWidget* dock2 = createDock(widget2, "Big 2 Widget");
        addDockWidget(Qt::RightDockWidgetArea, dock1);
        tabifyDockWidget(dock1, dock2);
    }
}

bool MainWindow::confirmApExit()
{
    return true;
}
