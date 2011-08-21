#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accessreader.h"
#include "indicatorsmodel.h"
#include "logindialog.h"
#include "settingsview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    timer.start(1000*60);

    createActions();
    createMainMenu();
    createTrayIcon();

    trayIcon.show();

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateModel()));
    connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inject(SettingsModel *settings, AccessReader *accessReader)
{
    this->settings = settings;
    this->accessReader = accessReader;
}


void MainWindow::updateView()
{
    ui->lcdAmount->display(indicatorsModel.getAmount());
    ui->lcdSum->display(indicatorsModel.getSum());
    ui->lcdCash->display(indicatorsModel.getCash());

    trayIcon.setToolTip(tr("Текущий пользователь: ") + settings->getUserName() + "\n" +
                        tr("Кол-во: ") + QString::number(indicatorsModel.getAmount()) + "\n" +
                        tr("Сумма: ") + QString::number(indicatorsModel.getSum()) + "\n" +
                        tr("Выручка: ") + QString::number(indicatorsModel.getCash()));
}

void MainWindow::updateModel()
{
    statusBar()->showMessage(tr("Получение данных..."));

    indicatorsModel = accessReader->getData();
    updateView();

    statusBar()->clearMessage();
}

void MainWindow::on_actionLogin_triggered()
{
    LoginDialog loginView;
    if (loginView.showDialog(settings, accessReader) == QDialog::Accepted) {

        updateView();
    }
}


void MainWindow::on_actionSettings_triggered()
{
    SettingsView settingsView;
    if (settingsView.exec() == QDialog::Accepted) {

    }
}

void MainWindow::on_aboutView_triggered()
{

}

void MainWindow::on_restoreAction_triggered()
{
    if (this->isVisible()) {
        this->hide();
    } else {
        this->showNormal();
    }

}
void MainWindow::createActions()
{
    loginAction = new QAction(tr("Сменить пользователя..."), this);
    connect(loginAction, SIGNAL(triggered()), this, SLOT(on_actionLogin_triggered()));

    settingsAction = new QAction(tr("Настройки"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(on_actionSettings_triggered()));

    aboutViewAction = new QAction(tr("О программе..."), this);
    connect(aboutViewAction, SIGNAL(triggered()), this, SLOT(on_aboutView_triggered()));

    restoreAction = new QAction(tr("Показать/Скрыть"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(on_restoreAction_triggered()));

    quitAction = new QAction(tr("В&ыход"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{

    trayIconMenu.addAction(restoreAction);
    trayIconMenu.addAction(loginAction);
    trayIconMenu.addAction(settingsAction);
    trayIconMenu.addSeparator();
    trayIconMenu.addAction(quitAction);

    trayIcon.setContextMenu(&trayIconMenu);

    trayIcon.setIcon(this->windowIcon());

}

void MainWindow::createMainMenu()
{
    ui->Filemenu->addAction(loginAction);
    ui->Filemenu->addSeparator();
    ui->Filemenu->addAction(restoreAction);
    ui->Filemenu->addAction(quitAction);
    ui->Servicemenu->addAction(settingsAction);
    ui->Helpmenu->addAction(aboutViewAction);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        on_restoreAction_triggered();
        break;
    case QSystemTrayIcon::MiddleClick:

        break;
    default:
        ;
    }
}
