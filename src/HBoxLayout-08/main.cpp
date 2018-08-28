#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QFontDatabase>
#include <QPushButton>
#include <QListWidget>

#include <QtPlugin>

#if defined(Q_OS_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;

    QPushButton* button1 = new QPushButton("button1");
    QPushButton* button2 = new QPushButton("button2");
    QPushButton* button3 = new QPushButton("button3");
    QPushButton* button4 = new QPushButton("button4");

    // first create the four widgets at the top left,
    // and use QWidget::setFixedWidth() on each of them.

    // then set up the top widget (composed of the four smaller widgets):
    QWidget *topWidget = new QWidget;
    QHBoxLayout *topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->addWidget(button1);
    topWidgetLayout->addWidget(button2);
    topWidgetLayout->addWidget(button3);
    topWidgetLayout->addWidget(button4);
    topWidgetLayout->addStretch(1); // add the stretch
    topWidget->setFixedHeight(50);

    QListWidget* bottomWidget = new QListWidget;

    // now put the bottom (centered) widget into its own QHBoxLayout
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(bottomWidget);
    hLayout->addStretch(1);
    bottomWidget->setFixedSize(QSize(50, 50));

    // now use a QVBoxLayout to lay everything out
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topWidget);
    mainLayout->addStretch(1);
    mainLayout->addLayout(hLayout);
    mainLayout->addStretch(1);

    window.setLayout(mainLayout);

    window.show();

    return a.exec();
}
