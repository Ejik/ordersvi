#include <QDebug>
#include <QSqlError>
#include "accessreader.h"
#include <QtGlobal>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QDate>
#include <QVariant>

AccessReader::AccessReader()
{
    connectionCreated = false;
}

AccessReader::~AccessReader()
{
    db.close();
}

void AccessReader::bindObjects(SettingsModel *settings)
{
    this->settings = settings;
}

IndicatorsModel AccessReader::getData() {

    IndicatorsModel model;   

    if (!connectionCreated) {
        createConnection();
    }

    if (connectionCreated)
    {

        QDate currentDate = QDate::currentDate();
        QString month = QString::number(currentDate.month());
        QString year = QString::number(currentDate.year());
        QString date1 = "#1\\1\\2010#"; //"#" + month + "\\1\\" + year + "#";
        QString date2 = "#1\\4\\2010#"; //"#" + month + "\\" + QString::number(currentDate.daysInMonth())+ "\\" + year + "#";        

        QSqlQuery query;

        QString sql = "SELECT COUNT(1) AS Amount, SUM(DH2457.SP2451) AS Summa , Users.ID AS ManagerID "
                "FROM (DH2457 INNER JOIN _1SJOURN AS Journal ON DH2457.IDDOC=Journal.IDDOC) "
                "INNER JOIN SC30 AS Users ON Journal.SP74 = Users.ID "
                "WHERE Users.ID = :userID "
                "AND Journal.Date Between :date1 AND :date2 "
                "GROUP BY Users.ID;";


        query.prepare(sql);

        query.bindValue(":date1", QDate(2010,1,1));
        query.bindValue(":date2", QDate(2010,1,4));
        query.bindValue(":userID", settings->getUserID());

        if (query.exec()) {

            query.first();
            if (query.isValid()) {
                model.setAmount(query.value(0).toInt());
                model.setSum(query.value(1).toInt());
                model.setCash(0);
            }
        } else {
            qDebug() << query.lastError();
        }
    }
    return model;
}

bool AccessReader::createConnection() {

    db = QSqlDatabase::addDatabase("QODBC");
    db.setUserName("admin");
    //db.setPassword();

    // текущий каталог базы
    QString dbFilename = QDir::toNativeSeparators(QDir::currentPath() + "\\db.mdb");

    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};"
                       "FIL={MS Access};DBQ=db.mdb");//" + dbFilename);

    if (!db.open()) {
        return false;
    }


    this->connectionCreated = true;

    return true;
}

QMap<QString, QString> AccessReader::getUsersList()
{   
    if (!connectionCreated) {
        createConnection();
    }

    QMap<QString, QString> map;
    QSqlQuery query;

    QString sql = "SELECT ID, DESCR FROM SC30";


    if (!query.exec(sql)) {
        qDebug() << query.lastError();
    }
    while (query.next()) {
        map.insert(query.value(0).toString(), query.value(1).toString());
    }

    return map;
}
