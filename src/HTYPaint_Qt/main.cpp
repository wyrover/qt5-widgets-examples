#include "mainwindow.h"
#include <QApplication>
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    #include <QTextCodec>
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
Q_IMPORT_PLUGIN(QSvgPlugin)
Q_IMPORT_PLUGIN(QSvgIconPlugin)


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qSetMessagePattern("[ %{file}: %{line} ] %{message}");
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec *tc = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(tc);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#endif
    MainWindow w;
    w.show();
    return a.exec();
}
