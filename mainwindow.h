#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QTimer>
#include "accessreader.h"
#include "indicatorsmodel.h"
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
    void inject(SettingsModel* settings, AccessReader* accessReader);

private slots:

    void on_actionLogin_triggered();

    void updateModel();

    void on_actionSettings_triggered();

    void on_aboutView_triggered();

    void on_restoreAction_triggered();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    SettingsModel *settings;
    AccessReader *accessReader;
    IndicatorsModel indicatorsModel;

    QAction *loginAction;
    QAction *settingsAction;
    QAction *aboutViewAction;
    QAction *restoreAction;
    QAction *quitAction;

    QTimer timer;

    QSystemTrayIcon trayIcon;
    QMenu trayIconMenu;

    void createActions();
    void createMainMenu();
    void createTrayIcon();
    void updateView();
};

#endif // MAINWINDOW_H
