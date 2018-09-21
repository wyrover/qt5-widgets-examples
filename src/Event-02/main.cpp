#include "widget.h"
#include <QApplication>


#include <QtPlugin>

#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(200, 200);
    w.show();
    return a.exec();
}
