#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QFontDatabase>
#include <QPushButton>
#include <QListWidget>
#include <QDebug>

#include <QtPlugin>
#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

#ifdef WIN32
#include <windows.h>
#include <stdio.h>
#endif


void create_form_1()
{
        auto window = new QWidget;
        window->setWindowTitle("form_1");
        QPushButton* button1 = new QPushButton("button1");
        button1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        QPushButton* button2 = new QPushButton("button2");
        button2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

        QPushButton* button3 = new QPushButton("button3");
        QPushButton* button4 = new QPushButton("button4");

        auto layout = new QVBoxLayout;
        layout->addWidget(button1);
        layout->addWidget(button2);
        layout->addWidget(button3);
        layout->addWidget(button4);
        window->setLayout(layout);
        window->show();


        qDebug() << window->width() << "," << window->height();
        qDebug() << window->sizeHint().width() << "," << window->sizeHint().height();
}

    void create_form_2()
    {
        auto window = new QWidget;
        window->setWindowTitle("form_2");
               

        QPushButton* button1 = new QPushButton("button1");
        button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QPushButton* button2 = new QPushButton("button2");
        button2->setFixedWidth(100);
        button2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        QPushButton* button3 = new QPushButton("button3");
        QPushButton* button4 = new QPushButton("button4");

        auto layout = new QHBoxLayout;
        layout->addWidget(button1);
        layout->addWidget(button2);
        layout->addWidget(button3);
        layout->addWidget(button4);
        window->setLayout(layout);
        window->show();


        qDebug() << window->width() << "," << window->height();
        qDebug() << window->sizeHint().width() << "," << window->sizeHint().height();
    }



    void create_form_3()
    {
        auto window = new QWidget;
        window->setWindowTitle("form_3");
        QPushButton* button1 = new QPushButton("button1");
        button1->setMinimumWidth(300);
        button1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

        QPushButton* button2 = new QPushButton("button2");
     
        button2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        QPushButton* button3 = new QPushButton("button3");
        QPushButton* button4 = new QPushButton("button4");

        auto layout = new QHBoxLayout;
        layout->addWidget(button1);
        layout->addWidget(button2);
        layout->addWidget(button3);
        layout->addWidget(button4);
        window->setLayout(layout);
        window->show();


        qDebug() << window->width() << "," << window->height();
        qDebug() << window->sizeHint().width() << "," << window->sizeHint().height();
    }

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

    QApplication a(argc, argv);
    
    create_form_1();
    create_form_2();
    create_form_3();

    return a.exec();
}
