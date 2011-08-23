#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QSettings>

class SettingsModel
{

private:

    bool isAlwaysOnTop;
    bool isAutoStart;
    QString appFilePath;
    QString userid;
    QString userName;

public:
    SettingsModel(QString appFilePath) { userid = ""; userName = ""; isAlwaysOnTop = false; this->appFilePath = appFilePath; }

    bool getAlwaysOnTop() { return isAlwaysOnTop; }
    void setAlwaysOnTop(bool value) { isAlwaysOnTop  = value; }

    QString getUserID() { return userid; }
    void setUserID(QString value) { userid = value; }

    QString getUserName() { return userName; }
    void setUserName(QString value) { userName = value; }

    void setAutoStartApplication(bool start) {
#if defined(Q_WS_WIN)
        QSettings set("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        if (start)
            set.setValue("ordersvi", appFilePath);
        else
            set.remove("ordersvi");
#else
#endif

   }
    bool getAutoStartApplication()
    {
#if defined(Q_WS_WIN)
        QSettings set("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        if (!set.value("ordersvi").isNull())
            if (set.value("ordersvi").toString() == appFilePath)
                return true;
        return false;
#else
        return false;
#endif
    }
};
#endif // SETTINGSMODEL_H
