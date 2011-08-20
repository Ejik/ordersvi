#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <QDialog>
#include <QSqlTableModel>
#include "accessreader.h"

namespace Ui {
    class SettingsView;
}

class SettingsView : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = 0);
    ~SettingsView();
    void inject(AccessReader *accessReader);
private slots:

private:
    Ui::SettingsView *ui;
    QSqlTableModel tableModel;
    AccessReader *accessReader;
};

#endif // SETTINGSVIEW_H
