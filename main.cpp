#include <QDebug>
#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "logindialog.h"
#include "accessreader.h"
#include "settingsmodel.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(ordersvi);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    SettingsModel settings(a.applicationFilePath());
    AccessReader accessReader;
    accessReader.inject(&settings);

    LoginDialog loginView;
    if (loginView.showDialog(&settings, &accessReader) == QDialog::Accepted) {

        qDebug() << "Current userID: " << settings.getUserID();

        MainWindow w;
        w.show();
        w.inject(&settings, &accessReader);
        w.updateView();
        return a.exec();
    }
    return 0;
}
