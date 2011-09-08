#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>
#include <QSqlTableModel>
#include "accessreader.h"
#include "settingsmodel.h"

namespace Ui {
    class SettingsView;
}

class SettingsView : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = 0);
    ~SettingsView();
    void inject(SettingsModel *settings, AccessReader *accessReader);
    void updateView();
    bool isAlwaysOnTop();
    bool isAutostartApplication();

private slots:


private:
    Ui::SettingsView *ui;
    QSqlTableModel tableModel;
    AccessReader *accessReader;
    SettingsModel *settings;

    void updateNormsTable();
};

#endif // SETTINGSVIEW_H
