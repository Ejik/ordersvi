#include "indicatorsmodel.h"
#include <QMap>
#include <QSqlDatabase>

#ifndef ACCSESSREADER_H
#define ACCSESSREADER_H

class AccessReader
{
private:
    bool connectionCreated;
    bool createConnection();
    QSqlDatabase db;

public:
    AccessReader();
    ~AccessReader();
    IndicatorsModel getData();
    QMap<QString, QString> getUsersList();
};

#endif // ACCESSREADER_H
