#include "mainwindow.h"
#include <QApplication>

#include <QtPlugin>
#if defined(Q_OS_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

//Q_IMPORT_PLUGIN(QSQLiteDriverPlugin)
Q_IMPORT_PLUGIN(QICOPlugin)
//Q_IMPORT_PLUGIN(QJpegPlugin)
//Q_IMPORT_PLUGIN(QGifPlugin)
//Q_IMPORT_PLUGIN(QTgaPlugin)
Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QSvgIconPlugin)
#elif defined(Q_OS_MAC)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
