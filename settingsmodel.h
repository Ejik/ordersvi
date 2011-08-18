#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

class SettingsModel
{

private:
    int userid;
public:
    SettingsModel() { userid = 0; }
    int getUserID() { return userid; }
    void setUserID(int value) { userid = value; }

};
#endif // SETTINGSMODEL_H
