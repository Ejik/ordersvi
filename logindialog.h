#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "accessreader.h"
#include "settingsmodel.h"

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    int showDialog(SettingsModel* settings, AccessReader* accessReader);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
