#include "utils.h"
#include <QApplication>
#include <QFile>

QString getAppDir()
{
    return QCoreApplication::applicationDirPath();
}


void setQssStyle(const QString& qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());        
        qApp->setStyleSheet(qss);        
        file.close();
    }
}