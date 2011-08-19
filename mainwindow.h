#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accessreader.h"
#include "settingsmodel.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bindObjects(SettingsModel* settings, AccessReader* accessReader);

private slots:

    void on_actionLogin_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    SettingsModel *settings;
    AccessReader *accessReader;
};

#endif // MAINWINDOW_H
