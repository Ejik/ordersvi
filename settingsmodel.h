#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

class SettingsModel
{

private:
    QString userid;
public:
    SettingsModel() { userid = ""; }
    QString getUserID() { return userid; }
    void setUserID(QString value) { userid = value; }

};
#endif // SETTINGSMODEL_H
