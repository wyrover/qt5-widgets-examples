#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QtPlugin>

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#endif

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
#ifdef WIN32
        // detach from the current console window
        // if launched from a console window, that will still run waiting for the new console (below) to close
        // it is useful to detach from Qt Creator's <Application output> panel
        FreeConsole();
        // create a separate new console window
        AllocConsole();
        // attach the new console to this application's process
        AttachConsole(GetCurrentProcessId());
        SetConsoleOutputCP(65001);
        // reopen the std I/O streams to redirect I/O to the new console
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
        freopen("CON", "r", stdin);
#endif

    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    QFile qss(":/qss/assets/styles/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();


    Widget window;
   
    window.show();
    return a.exec();
}
