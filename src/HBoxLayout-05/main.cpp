#include "widget.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include <QtPlugin>

#if defined(Q_OS_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    QWidget* window = new QWidget;
    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addStretch();
    layout->addWidget(button1);
    layout->addStretch();
    layout->addWidget(button2);
    layout->addStretch();
    layout->addWidget(button3);
    layout->addStretch();
    layout->addWidget(button4);
    layout->addStretch();
    layout->addWidget(button5);
    layout->addStretch();  // 添加伸缩   每一个控件中间都加，所有控件均分

    window->setLayout(layout);
    window->show();

    return a.exec();
}
