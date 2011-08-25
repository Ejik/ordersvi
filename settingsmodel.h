#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QPoint>
#include <QSettings>


class SettingsModel
{

private:

    bool isAlwaysOnTop;
    bool isAutoStart;
    QString appFilePath;
    QString userid;
    QString username;
    QPoint _mainViewPos;

public:
    SettingsModel(QString appFilePath) { userid = ""; username = ""; isAlwaysOnTop = false; this->appFilePath = appFilePath; }

    QString userID() { return userid; }
    void setUserID(QString value) { userid = value; }

    QString userName() { return username; }
    void setUserName(QString value) { username = value; }

    bool alwaysOnTop() { return isAlwaysOnTop; }
    void setAlwaysOnTop(bool value) { isAlwaysOnTop  = value; }

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

    QPoint mainViewPos() { return _mainViewPos; }
    void setMainViewPos(QPoint value) { _mainViewPos = value; }

    void save() {
        QSettings settings;
        settings.setValue("isAlwaysOnTop", isAlwaysOnTop);
        settings.setValue("isAutoStart", isAutoStart);
        settings.setValue("lastUserID", userid);
        settings.setValue("mainViewPos", _mainViewPos);

    }
    void restore() {

        QSettings settings;
        isAlwaysOnTop = settings.value("isAlwaysOnTop",  false).toBool();
        isAutoStart = settings.value("isAutoStart", false).toBool();
        userid = settings.value("lastUserID", "").toString();
        _mainViewPos = settings.value("mainViewPos", QPoint(200,200)).toPoint();
    }
};
#endif // SETTINGSMODEL_H
