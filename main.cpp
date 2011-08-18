#include <QDebug>
#include <QtGui/QApplication>
#include "mainwindow.h"
#include "logindialog.h"
#include "accessreader.h"
#include "settingsmodel.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SettingsModel settings;
    AccessReader accessReader;

    LoginDialog loginDlg;
    if (loginDlg.showDialog(&settings, &accessReader) == QDialog::Accepted)
    {
        qDebug() << settings.getUserID();

        MainWindow w;
        w.show();

        return a.exec();
    }

    return 0;
}
