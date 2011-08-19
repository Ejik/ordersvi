#include "indicatorsmodel.h"
#include <QMap>
#include <QSqlDatabase>
#include "settingsmodel.h"

#ifndef ACCSESSREADER_H
#define ACCSESSREADER_H

class AccessReader
{
private:
    bool connectionCreated;
    bool createConnection();
    QSqlDatabase db;
    SettingsModel *settings;

public:
    AccessReader();
    ~AccessReader();
    IndicatorsModel getData();
    QMap<QString, QString> getUsersList();
    void bindObjects(SettingsModel *settings);
};

#endif // ACCESSREADER_H
