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

void AccessReader::inject(SettingsModel *settings)
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


//        QString month = QString::number(currentDate.month());
//        QString year = QString::number(currentDate.year());
//        QString date1 = "#1\\1\\2010#"; //"#" + month + "\\1\\" + year + "#";
//        QString date2 = "#1\\4\\2010#"; //"#" + month + "\\" + QString::number(currentDate.daysInMonth())+ "\\" + year + "#";

        QSqlQuery query;

        QString sql = "SELECT COUNT(1) AS Amount, SUM(DH2457.SP2451) AS Summa, ZaprosCash.Cash AS Cash, Users.ID "
                "FROM ((DH2457 INNER JOIN _1SJOURN AS Journal ON DH2457.IDDOC=Journal.IDDOC) "
                "INNER JOIN SC30 AS Users ON Journal.SP74 = Users.ID) "
                "LEFT JOIN ( "
                "SELECT Users.ID AS ManagerID, SUM(RA4674.SP4673) AS Cash "
                "FROM (RA4674 INNER JOIN _1SJOURN AS Journal ON RA4674.SP4671=Journal.IDDOC) "
                "INNER JOIN SC30 AS Users ON Journal.SP74=Users.ID "
                "WHERE RA4674.DEBKRED=1 AND Journal.ISMARK IS NULL "
                "AND Journal.Date Between :date1 AND :date2 "
                "GROUP BY Users.ID) AS ZaprosCash "
                "ON Users.ID = ZaprosCash.ManagerID "
                "WHERE Journal.ISMARK IS NULL "
                "AND Users.ID = :userID "
                "AND Journal.Date Between :date1 AND :date2 "
                "GROUP BY Users.ID, ZaprosCash.Cash;";


        query.prepare(sql);

        int amount = 0;
        int summa = 0;
        int cash = 0;


        QDate currentDate = QDate::currentDate();
        int currentYear = currentDate.year();
        int currentMonth = currentDate.month();
        int daysInCurrentMonth = currentDate.daysInMonth();

        query.bindValue(":date1", QDate(currentYear, currentMonth, 1));
        query.bindValue(":date2", QDate(currentYear, currentMonth, daysInCurrentMonth));
        query.bindValue(":userID", settings->userID());

        if (query.exec()) {

            query.first();
            if (query.isValid()) {
                amount = query.value(0).toInt();
                summa = query.value(1).toInt();
                cash = query.value(2).toInt();
            }
        } else {
            qDebug() << query.lastError();
        }

        model.setAmount(amount);
        model.setSum(summa);
        model.setCash(cash);

        // Получаем нормативные показатели за месяц
        QSqlQuery normsQuery;
        sql = "SELECT * "
                "FROM Norms "
                "WHERE USERID = :userID";
        normsQuery.prepare(sql);
        normsQuery.bindValue(":userID", settings->userID());
        if (normsQuery.exec()) {

            model.setNAmount(0);
            model.setNSum(0);
            model.setNCash(0);

            if (normsQuery.size() > 0) {
                // Кол-во
                normsQuery.next();
                model.setNAmount(normsQuery.value(currentMonth + 1).toInt());

                // Сумма
                normsQuery.next();
                model.setNSum(normsQuery.value(currentMonth + 1).toInt());

                // Выручка
                normsQuery.next();
                model.setNCash(normsQuery.value(currentMonth + 1).toInt());
            }

        } else {
            qDebug() << normsQuery.lastError();
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
