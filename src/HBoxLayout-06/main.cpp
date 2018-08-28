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
    // 水平居左 垂直居上
    layout->addWidget(button1, 0 , Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(button2, 0 , Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(button3);
    // 水平居左 垂直居下
    layout->addWidget(button4, 0 , Qt::AlignLeft | Qt::AlignBottom);
    layout->addWidget(button5, 0 , Qt::AlignLeft | Qt::AlignBottom);
    layout->setSpacing(10);
    window->setLayout(layout);
    window->show();
    return a.exec();
}
