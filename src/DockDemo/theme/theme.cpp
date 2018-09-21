#include "theme.h"

#include <QApplication>
#include <QDebug>


static const QLatin1String THEME_PREFIX("Theme.");
static const QLatin1String THEME_NAMES("Names");
static const QLatin1String THEME_COMMON("Theme");


static const int MAX_SUBSTUTUTION_DEEP = 5;


static Theme* instance;

static QString sectionName(const QString& name)
{
    return THEME_PREFIX + name;
}

Theme* theme()
{
    return Theme::instance();
}

QColor themeColor(const QString& key)
{
    return Theme::instance()->color(key);
}

bool extractSubstitute(const QString& s, QString& extracted)
{
    if (s.startsWith("[") && s.endsWith("]")) {
        extracted = s.mid(1, s.length() - 2);
        return true;
    } else {
        return false;
    }
}

// --- ThemeManager -----------------------------------------------------------

const QLatin1String Theme::MAIN_BACKGROUND("Main.Background");
const QLatin1String Theme::MENU_BACKGROUND("Menu.Background");
const QLatin1String Theme::MENU_TEXT("Menu.Text");
const QLatin1String Theme::MENU_BORDER("Menu.Border");
const QLatin1String Theme::MENU_SELECTED_BACKGROUND("Menu.Selected.Background");
const QLatin1String Theme::MENU_SELECTED_TEXT("Menu.Selected.Text");
const QLatin1String Theme::MENU_PRESSED_BACKGROUND("Menu.Pressed.Background");
const QLatin1String Theme::MENU_PRESSED_TEXT("Menu.Pressed.Text");
const QLatin1String Theme::STATUSBAR_BACKGROUND("StatusBar.Background");
const QLatin1String Theme::STATUSBAR_BORDER("StatusBar.Border");
const QLatin1String Theme::STATUSBAR_TEXT("StatusBar.Text");
const QLatin1String Theme::DOCK_BACKGROND("Dock.Background");
const QLatin1String Theme::DOCK_BORDER("Dock.Border");
const QLatin1String Theme::DOCK_TITLE_BACKGROUND("Dock.Title.Background");
const QLatin1String Theme::DOCK_TITLE_BORDER("Dock.Title.Border");
const QLatin1String Theme::DOCK_TITLE_TEXT("Dock.Title.Text");
const QLatin1String Theme::WIDGET_BACKGROUND("Widget.Background");
const QLatin1String Theme::WIDGET_BORDER("Widget.Border");
const QLatin1String Theme::WIDGET_TEXT("Widget.Text");


Theme::Theme(const QString& configFileName, QObject *parent) :
    QObject(parent),
    settings(configFileName, QSettings::IniFormat)
{
    //
}

Theme::~Theme()
{
    //
}

void Theme::create(const QString& configFileName, QObject* parent)
{
    if (::instance) {
        qDebug() << "duplicating ThemeManager";
        return;
    }

    ::instance = new Theme(configFileName, parent);
}

Theme* Theme::instance()
{
    return ::instance;
}

QStringList Theme::getThemeNames()
{
    settings.sync();
    QStringList names = settings.value(THEME_NAMES).toStringList();
    return names;
}

void Theme::load(const QString& name)
{
    map.clear();
    result.clear();
    settings.sync();
    QStringList names = settings.value(THEME_NAMES).toStringList();

    try {
        if (names.isEmpty()) {
            throw QString("No theme found");
        }

        if (!names.contains(name)) {
            throw QString("Theme not found: %1").arg(name);
        }

        if (!settings.childGroups().contains(sectionName(name))) {
            throw QString("Theme section not found: %1").arg(name);
        }

        // read THEME_COMMON, then override it by sectionName(name)
        Q_FOREACH (QString section, QStringList() << THEME_COMMON << sectionName(name)) {
            settings.beginGroup(section);

            Q_FOREACH (QString key, settings.allKeys()) {
                map[key] = settings.value(key).toString();
            }

            settings.endGroup();
        }
    } catch (const QString& error) {
        emit onError(error);
        return;
    }

    emit onLoaded();
}

QColor Theme::color(const QString& key)
{
    if (!result.contains(key)) {
        try {
            QString value = substitute(key);
            QColor clr = QColor(value);

            if (!clr.isValid()) {
                throw QString("Invalid color for '%1': %2").arg(key).arg(value);
            }

            result[key] = clr;
        } catch (const QString& error) {
            emit onError(error);
            return QColor();
        }
    }

    return result[key];
}

QString Theme::substitute(const QString& key)
{
    QString k = key;
    QString value;
    int maxCount = MAX_SUBSTUTUTION_DEEP;

    do {
        if (maxCount-- == 0) {
            throw QString("Too deep substitution: %1").arg(k);
        }

        if (!map.contains(k)) {
            throw QString("Theme item not defined: %1").arg(k);
        }

        value = map[k];
    } while (extractSubstitute(value, k));

    return value;
}

