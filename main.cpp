#include <QDebug>
#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "logindialog.h"
#include "accessreader.h"
#include "settingsmodel.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);


    SettingsModel settings;
    AccessReader accessReader;
    accessReader.inject(&settings);

    LoginDialog loginView;
    if (loginView.showDialog(&settings, &accessReader) == QDialog::Accepted) {

        qDebug() << "Current userID " << settings.getUserID();

        MainWindow w;
        w.show();
        w.inject(&settings, &accessReader);

        return a.exec();
    }
    return 0;
}
