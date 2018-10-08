#include "widget.h"
#include "tabwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>

#define	MAX_THREADS 4

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , mMdiArea(this)
{
    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);


    mMdiArea.setViewMode(QMdiArea::TabbedView);
    mMdiArea.setTabsClosable(true);
    mMdiArea.setTabsMovable(true);
    //mMdiArea.setDocumentMode(true);
    layout->addWidget(&mMdiArea);


    setLayout(layout);

    for (unsigned int i = 0; i < MAX_THREADS; i++) {
        this->newThread();
    }

    //mMdiArea.setViewMode(QMdiArea::SubWindowView);
    //mMdiArea.tileSubWindows();
}

Widget::~Widget()
{

}

void Widget::newThread()
{
    static int windowCount = 1;

    if (mMdiArea.subWindowList().count() == MAX_THREADS) {
        QMessageBox::information(0, "No, no, no...",
            "Maximum Nr. of open documents reached"
            "Dont torture your computer!");
        return;
    }

    QTextEdit *widget = new QTextEdit(&mMdiArea);
    mMdiArea.addSubWindow(widget);
    widget->setWindowTitle("Thread #" + QString::number(windowCount++));
    widget->show();
    
}
