#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_actionExit_triggered();

    void updateModel();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;
    SettingsModel *settings;
    AccessReader *accessReader;
    IndicatorsModel indicatorsModel;
    QTimer timer;

    void updateIndicators();
};

#endif // MAINWINDOW_H
