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
    accessReader.bindObjects(&settings);

    LoginDialog loginView;
    if (loginView.showDialog(&settings, &accessReader) == QDialog::Accepted) {

        qDebug() << "Current userID " << settings.getUserID();

        MainWindow w;
        w.show();
        w.bindObjects(&settings, &accessReader);

        return a.exec();
    }
    return 0;
}
