#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

class Settings {

private:
    int userid;
public:
    int getUserID();
    void setUserID(int value) { userid = value; }

}
#endif // SETTINGSMODEL_H
