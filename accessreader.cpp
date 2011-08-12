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
}

IndicatorsModel AccessReader::getData() {

    IndicatorsModel model;

    if (createConnection()) {

        QDate currentDate = QDate::currentDate();
        QString month = QString::number(currentDate.month());
        QString year = QString::number(currentDate.year());
        QString date1 = "#1\\1\\2010#"; //"#" + month + "\\1\\" + year + "#";
        QString date2 = "#1\\4\\2010#"; //"#" + month + "\\" + QString::number(currentDate.daysInMonth())+ "\\" + year + "#";

        QSqlQuery query;

        QString sql = "SELECT COUNT(DH2457.SP2451) AS Amount, SUM(DH2457.SP2451) AS Summa "
                "FROM DH2457 LEFT JOIN _1SJOURN AS Journal ON DH2457.IDDOC=Journal.IDDOC "
                "WHERE (((Journal.Date) Between ?date1 AND ?date2))";
        sql = "SELECT Amount, Summa FROM Zapros";

        query.prepare(sql);

        query.bindValue(":date1", date1);
        query.bindValue(":date2", date2);

        if (query.exec(sql)) {

            query.next();

            model.setAmount(query.value(0).toInt());
            model.setSum(query.value(1).toInt());
            model.setCash(0);
        } else {
            qDebug() << query.lastError();
        }
    }
    return model;
}

bool AccessReader::createConnection() {

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setUserName("admin");
    //db.setPassword();

    // текущий каталог базы
    QString dbFilename = QDir::toNativeSeparators(QDir::currentPath() + "\\db.mdb");

    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};"
                       "FIL={MS Access};DBQ=db.mdb");//" + dbFilename);

    if (!db.open()) {
        return false;
    }

    //db.close();
    return true;
}
