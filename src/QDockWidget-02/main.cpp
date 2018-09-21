#include <QApplication>

#include "rqttest.h"

int main(int argc, char *argv[])
{
    RInside R(argc, argv);
    QApplication app(argc, argv);
    QApplication::setCursorFlashTime(0);
    RQtTest rqttest(R);
    rqttest.show();
    return app.exec();
}
