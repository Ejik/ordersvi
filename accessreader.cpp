#include <QDebug>
#include "accessreader.h"
#include <QtGlobal>
#include <QtSql/QSqlDatabase>
#include <QDir>

AccessReader::AccessReader()
{
}

IndicatorsModel AccessReader::getData() {

    IndicatorsModel model;

    if (createConnection()) {

        qsrand(10000);

        model.setAmount(qrand());
        model.setSum(qrand());
        model.setCash(qrand());

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
