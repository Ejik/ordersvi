#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::showDialog(SettingsModel* settings, AccessReader* accessReader)
{
    settings->setUserID(123);

    return this->exec();
}
