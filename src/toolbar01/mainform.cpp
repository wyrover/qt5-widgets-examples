#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "mainform.h"
#include "ui_mainform.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QListWidget>



    MainForm::MainForm(QWidget *parent) :
        QWidget(parent)

{
    layout_ = new QVBoxLayout;
    auto toolbar = new QToolBar(this);
    toolbar->addAction(QIcon(":/icons/refresh.png"), tr("Refresh"));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/icons/install.png"), tr("Install"));
    toolbar->addAction(QIcon(":/icons/delete.png"), tr("Uninstall"))->setEnabled(false);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/icons/enable.png"), tr("Enable"))->setEnabled(false);
    toolbar->addAction(QIcon(":/icons/disable.png"), tr("Disable"))->setEnabled(false);
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/icons/apk.png"), tr("Extract APK"))->setEnabled(false);
    //toolBarMain->setStyleSheet("background-color:rgb(200,40,43);color:rgb(204,204,204)");
    auto list_widget_ = new QListWidget;
    layout_->addWidget(toolbar);
    create_svg_toolbar();
    layout_->addWidget(list_widget_);
    layout_->setContentsMargins(0, 0, 0, 0);
    setLayout(layout_);
    resize(800, 600);
}

MainForm::~MainForm()
{
}

void MainForm::onToolbarClicked(bool checked)
{
}

void MainForm::create_svg_toolbar()
{
    auto toolbar = new QToolBar(this);
    toolbar->addAction(QIcon(":/svg/material_icons/ic_apps_white_48px.svg"), tr("Refresh"));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/svg/material_icons/ic_bug_report_white_48px.svg"), tr("Install"));
    toolbar->addAction(QIcon(":/svg/material_icons/ic_build_white_48px.svg"), tr("Uninstall"));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/svg/material_icons/ic_create_white_48px.svg"), tr("Enable"));
    toolbar->addAction(QIcon(":/svg/material_icons/ic_format_align_left_white_48px.svg"), tr("Disable"));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/svg/material_icons/ic_help_white_48px.svg"), tr("Extract APK"));
    layout_->addWidget(toolbar);
}
