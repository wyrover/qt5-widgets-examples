#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

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
Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QSvgIconPlugin)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qSetMessagePattern("[ %{file}: %{line} ] %{message}");
    /*  Qt5以下：
        QTextCodec *tc = QTextCodec::codecForName("UTF-8");
        QTextCodec::setCodecForTr(tc);
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    */
    MainWindow w;
    w.show();
    return app.exec();
}
