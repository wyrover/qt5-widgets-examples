#include "mainwindow.h"

#include <CuteLogger/include/Logger.h>
#include <CuteLogger/include/ConsoleAppender.h>
#include <CuteLogger/include/FileAppender.h>

#include <QApplication>

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#endif

#include <QtPlugin>

#if defined(Q_OS_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif


Q_IMPORT_PLUGIN(QICOPlugin)
//Q_IMPORT_PLUGIN(QJpegPlugin)
//Q_IMPORT_PLUGIN(QGifPlugin)
//Q_IMPORT_PLUGIN(QTgaPlugin)
//Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QSvgIconPlugin)



int main(int argc, char *argv[])
{
#ifdef _DEBUG
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
#endif
    QString cmd = u8"中文测试";
    qDebug() << cmd.toUtf8().data();

    QApplication a(argc, argv);

    ConsoleAppender* consoleAppender = new ConsoleAppender();
    cuteLogger->registerAppender(consoleAppender);


    MainWindow w;
    w.show();

    return a.exec();
}
