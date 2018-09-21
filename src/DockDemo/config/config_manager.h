#pragma once

#include <QObject>
#include <QList>
#include <QSettings>


class QSettings;


class ConfigManager :
    public QObject
{
    Q_OBJECT

public:
    explicit ConfigManager(const QString& configFileName, QObject* parent = NULL);
    ~ConfigManager();

public:
    void set(const QString& key, const QVariant& value);
    QVariant get(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void sync();

public:
    QStringList getConfigNames();
    void save(const QString& name);
    void saveDefault();
    void load(const QString& name);
    void loadDefault();
    void remove(const QString& name);

Q_SIGNALS:
    void onSave();
    void onLoad();
    void onError(const QString& error);
    void onChanged();

private:
    QSettings               settings;
};

extern ConfigManager* config;
