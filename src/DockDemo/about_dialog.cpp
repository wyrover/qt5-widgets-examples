#include "about_dialog.h"
#include "ui_about_dialog.h"
#include "theme/theme.h"
#include "theme/stylesheet_builder.h"


static AboutDialog* instance;


void showAbout(QWidget* parent)
{
    if (!instance) {
        instance = new AboutDialog(parent);
    }

    instance->exec();
}


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(ui->btnClose, &QPushButton::clicked, this, &AboutDialog::accept);
    connect(theme(), &Theme::onLoaded, this, &AboutDialog::updateTheme);
    updateTheme();
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::updateTheme()
{
}
