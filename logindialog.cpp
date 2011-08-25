#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMap>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::showDialog(SettingsModel *settings, AccessReader *accessReader)
{

    QMap<QString, QString> userslist = accessReader->getUsersList();
    QMapIterator<QString, QString> i(userslist);
    int lastUserIdIndex(0);
    int idx(0);

    while (i.hasNext()) {
        i.next();
        ui->userCombo->addItem(i.value(), i.key());

        if (settings->userID().compare(i.key()) == 0) {
            lastUserIdIndex = idx;
        }
        idx++;
    }

    ui->userCombo->setCurrentIndex(lastUserIdIndex);
    int result =  this->exec();
    if (result == QDialog::Accepted) {
        settings->setUserID(ui->userCombo->itemData(ui->userCombo->currentIndex()).toString());
        settings->setUserName(ui->userCombo->itemText(ui->userCombo->currentIndex()));        
    }
    return result;
}
