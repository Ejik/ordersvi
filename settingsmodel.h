#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

class SettingsModel
{

private:
    QString userid;
    QString userName;

public:
    SettingsModel() { userid = ""; }

    QString getUserID() { return userid; }
    void setUserID(QString value) { userid = value; }

    QString getUserName() { return userName; }
    void setUserName(QString value) { userName = value; }
};
#endif // SETTINGSMODEL_H
