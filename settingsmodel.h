#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

class SettingsModel
{

private:
    bool alwaysOnTop;
    QString userid;
    QString userName;

public:
    SettingsModel() { userid = ""; userName = ""; alwaysOnTop = false; }

    bool getAlwaysOnTop() { return alwaysOnTop; }
    void setAlwaysOnTop(bool value) { alwaysOnTop  = value; }

    QString getUserID() { return userid; }
    void setUserID(QString value) { userid = value; }

    QString getUserName() { return userName; }
    void setUserName(QString value) { userName = value; }
};
#endif // SETTINGSMODEL_H
