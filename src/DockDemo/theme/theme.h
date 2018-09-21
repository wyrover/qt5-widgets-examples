#pragma once

#include <QStringList>
#include <QSettings>
#include <QColor>
#include <QMap>


class Theme :
    public QObject
{
    Q_OBJECT

public:
    static const QLatin1String MAIN_BACKGROUND;
    static const QLatin1String MENU_BACKGROUND;
    static const QLatin1String MENU_TEXT;
    static const QLatin1String MENU_BORDER;
    static const QLatin1String MENU_SELECTED_BACKGROUND;
    static const QLatin1String MENU_SELECTED_TEXT;
    static const QLatin1String MENU_PRESSED_BACKGROUND;
    static const QLatin1String MENU_PRESSED_TEXT;
    static const QLatin1String STATUSBAR_BACKGROUND;
    static const QLatin1String STATUSBAR_BORDER;
    static const QLatin1String STATUSBAR_TEXT;
    static const QLatin1String DOCK_BACKGROND;
    static const QLatin1String DOCK_BORDER;
    static const QLatin1String DOCK_TITLE_BACKGROUND;
    static const QLatin1String DOCK_TITLE_BORDER;
    static const QLatin1String DOCK_TITLE_TEXT;
    static const QLatin1String WIDGET_BACKGROUND;
    static const QLatin1String WIDGET_BORDER;
    static const QLatin1String WIDGET_TEXT;

private:
    explicit Theme(const QString& configFileName, QObject* parent = NULL);
    ~Theme();

public:
    static void create(const QString& configFileName, QObject* parent = NULL);
    static Theme* instance();

public:
    QStringList getThemeNames();
    void load(const QString& configFileName);
    QColor color(const QString& key);

Q_SIGNALS:
    void onError(const QString& error);
    void onLoaded();

private:
    QString substitute(const QString& key);

private:
    QSettings                   settings;
    QMap<QString, QString>      map;
    QMap<QString, QColor>       result;
};

Theme* theme();
QColor themeColor(const QString& key);
