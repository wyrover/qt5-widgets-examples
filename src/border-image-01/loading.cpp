#include "loading.h"

#include <QLabel>
#include <QMovie>
#include <QtWidgets/QApplication>
#include <QVBoxLayout>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>
#include <Windows.h>

void ve_sleep(int ms)
{
#ifdef WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

VSCLoading::VSCLoading(QWidget *parent)
    : QWidget(parent)
{
#if 1
    this->setFixedSize(64, 64);
    int width = this->width();

    //this->setWindowOpacity(0.5);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color: transparent;");
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));
    setPalette(pal);

    setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint | Qt::ToolTip);

    //setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint| Qt::ToolTip);

    QVBoxLayout *m_Layout = new QVBoxLayout();
    m_Layout->setMargin(0);

    setLayout(m_Layout);
    m_label = new QLabel(this);
    m_Layout->addWidget(m_label);
    //m_tip_label = new QLabel(this);
    //m_label->setStyleSheet("color: white; background-color: transparent;");
    //m_tip_label->setStyleSheet("color: white; background-color: transparent;");
    //m_label->setGeometry(0, 0, 64, 64);
    m_movie = new QMovie(":/action/resources/loading.gif");
    m_label->setScaledContents(true);
    m_label->setMovie(m_movie);
    m_movie->start();
    QIcon icon;
    icon.addFile(QStringLiteral(":/action/resources/libuivsc32.png"), QSize(), QIcon::Normal, QIcon::Off);
    this->setWindowIcon(icon);
    show();
#else
    this->setFixedSize(64, 64);
    int width = this->width();
    this->setWindowOpacity(0.8);
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background-color: rgb(42, 42, 43, 33);");

    //this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_label = new QLabel(this);
    //m_tip_label = new QLabel(this);
    m_label->setStyleSheet("background-color: transparent;");
    //m_tip_label->setStyleSheet("color: white; background-color: transparent;");
    m_label->setGeometry(0, 0, 64, 64);
    m_movie = new QMovie(":/action/resources/loading.gif");
    m_label->setScaledContents(true);
    m_label->setMovie(m_movie);
    m_movie->start();
    show();
#endif
}

VSCLoading::~VSCLoading()
{
    m_movie->stop();
}

void VSCLoading::Processing(int cnt)
{
    show();
    while (cnt--) {
        QCoreApplication::processEvents();
        ve_sleep(100);
    }
}

VSCLoading * VSCLoading::Create()
{
    VSCLoading *loading = new VSCLoading(NULL);
    loading->show();
    QDesktopWidget *desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(0);
    loading->setGeometry(rect.width() / 2, rect.height() / 2, 64, 64);
    QCoreApplication::processEvents();

    return loading;
}