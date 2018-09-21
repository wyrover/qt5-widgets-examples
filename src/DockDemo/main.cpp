#include "main_window.h"
#include "config/config_manager.h"
#include "theme/theme.h"
#include "utils.h"

#include <QApplication>

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
    config = new ConfigManager(changeFileExt(app.applicationFilePath(), ".ini"), &app);
    Theme::create(changeFileExt(app.applicationFilePath(), ".theme.ini"), &app);
    MainWindow* window = new MainWindow();
    window->show();
    return app.exec();
}
