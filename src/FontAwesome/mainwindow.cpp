#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fontawesomeicons.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    font(FontAwesomeIcons::Instance().getFont())
{
    ui->setupUi(this);
    this->font.setPointSize(16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QColor("#000000"));
    painter.setFont(this->font);

    painter.drawText(10,30, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_android));
    painter.drawText(30,30, "icon_android");

    painter.drawText(200,30, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_desktop));
    painter.drawText(230,30, "icon_desktop");

    painter.drawText(10,70, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_user));
    painter.drawText(30,70, "icon_user");

    painter.drawText(200,70, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_github));
    painter.drawText(230,70, "icon_github");

    painter.drawText(10,110, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_circle));
    painter.drawText(30,110, "icon_circle");

    painter.drawText(200,110, FontAwesomeIcons::Instance().getIconChar(FontAwesomeIcons::IconIdentity::icon_circle_blank));
    painter.drawText(230,110, "icon_circle_blank");

}
