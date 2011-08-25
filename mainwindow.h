#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QEvent>
#include <QMainWindow>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QTimer>
#include "accessreader.h"
#include "indicatorsmodel.h"
#include "settingsmodel.h"
#include "src/nightcharts.h"

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
    void init();
    void updateView();

private slots:

    void aboutView_triggered();
    void actionSettings_triggered();
    void actionLogin_triggered();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void restoreAction_triggered();
    void updateModel();


private:
    Ui::MainWindow *ui;
    SettingsModel *settings;
    AccessReader *accessReader;
    IndicatorsModel indicatorsModel;
    Nightcharts amountChart;
    Nightcharts sumChart;
    Nightcharts cashChart;

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
    void setAlwaysOnTopSetting();

    void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *);
    void paintEvent(QPaintEvent *);


};


#endif // MAINWINDOW_H
