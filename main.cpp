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

    QCoreApplication::setOrganizationName("ACSGroup");
    QCoreApplication::setOrganizationDomain("acsgroup.com");
    QCoreApplication::setApplicationName("OrdersVi");

    SettingsModel settings(a.applicationFilePath());
    settings.restore();

    AccessReader accessReader;
    accessReader.inject(&settings);

    LoginDialog loginView;
    if (loginView.showDialog(&settings, &accessReader) == QDialog::Accepted) {

        qDebug() << "Current userID: " << settings.userID();

        MainWindow w;
        w.inject(&settings, &accessReader);
        w.show();
        // устанавливаем окно на старое место
        w.move(settings.mainViewPos());
        w.updateView();
        return a.exec();

    }

    return 0;
}
