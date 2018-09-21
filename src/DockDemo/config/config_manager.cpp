#include "config_manager.h"

#include <QDebug>
#include <QString>
#include <QApplication>


static const QLatin1String CONFIG_PREFIX("Config.");
static const QLatin1String CONFIG_NAME("ConfigName");
static const QLatin1String CONFIG_NAMES("Config/Names");


static QString sectionName(const QString& name)
{
    return CONFIG_PREFIX + name;
}

ConfigManager* config;

// --- ConfigManager ----------------------------------------------------------

ConfigManager::ConfigManager(const QString& configFileName, QObject* parent) :
    QObject(parent),
    settings(configFileName, QSettings::IniFormat)
{
    //
}

ConfigManager::~ConfigManager()
{
    //
}

QStringList ConfigManager::getConfigNames()
{
    QStringList names = settings.value(CONFIG_NAMES).toStringList();
    names.removeOne(""); // remove default config
    return names;
}

void ConfigManager::set(const QString& key, const QVariant& value)
{
    settings.setValue(key, value);
}

QVariant ConfigManager::get(const QString& key, const QVariant& defaultValue) const
{
    return settings.value(key, defaultValue);
}

void ConfigManager::sync()
{
    settings.sync();
}

void ConfigManager::save(const QString& name)
{
    QStringList names = settings.value(CONFIG_NAMES).toStringList();

    if (names.contains(name)) {
        settings.remove(sectionName(name));
        names.removeOne(name);
    }

    names.append(name);
    settings.setValue(CONFIG_NAMES, names);
    settings.beginGroup(sectionName(name));
    settings.setValue(CONFIG_NAME, name);
    emit onSave();
    settings.endGroup();
    settings.sync();
    emit onChanged();
}

void ConfigManager::saveDefault()
{
    save("");
}

void ConfigManager::load(const QString& name)
{
    QStringList names = settings.value(CONFIG_NAMES).toStringList();

    if (!name.isEmpty() && !names.contains(name)) {
        onError("Config not found: " + name);
        return;
    }

    if (!settings.childGroups().contains(sectionName(name))) {
        onError("Config section not found: " + name);
        return;
    }

    settings.beginGroup(sectionName(name));
    emit onLoad();
    QString storedName = settings.value(CONFIG_NAME).toString();
    settings.endGroup();

    if (storedName != name) {
        emit onError(QString("Config name dismatch: stored: '%1', expected: '%2'").arg(storedName).arg(name));
    }
}

void ConfigManager::loadDefault()
{
    load("");
}

void ConfigManager::remove(const QString& name)
{
    QStringList names = settings.value(CONFIG_NAMES).toStringList();

    if (!names.contains(name)) {
        onError("Config not found: " + name);
        return;
    }

    settings.remove(sectionName(name));
    names.removeOne(name);
    settings.setValue(CONFIG_NAMES, names);
    settings.sync();
    emit onChanged();
}
