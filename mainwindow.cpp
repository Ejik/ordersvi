#include <QDebug>
#include <QPainter>
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


    timer.start(1000*6);

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

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    double width(this->width()/4);
    double height(this->height()/2);
    int i1Left(ui->lcdAmount->geometry().left() + 10);
    int i2Left(ui->lcdSum->geometry().left() + 10);
    int i3Left(ui->lcdCash->geometry().left() + 10);

    QColor i1Color(Qt::red);
    QColor i2Color(Qt::red);
    QColor i3Color(Qt::red);

    if ((indicatorsModel.getAmountPersent() >= 80) && ((indicatorsModel.getAmountPersent() < 95))) {
        i1Color = Qt::yellow;
    }
    if ((indicatorsModel.getSumPersent() >= 80) && ((indicatorsModel.getSumPersent() < 95))) {
        i2Color = Qt::yellow;
    }
    if ((indicatorsModel.getCashPersent() >= 80) && ((indicatorsModel.getCashPersent() < 95))) {
        i3Color = Qt::yellow;
    }

    if (indicatorsModel.getAmountPersent() >= 95) {
        i1Color = Qt::green;
    }
    if (indicatorsModel.getSumPersent() >= 95) {
        i2Color = Qt::green;
    }
    if (indicatorsModel.getCashPersent() >= 95) {
        i3Color = Qt::green;
    }


    amountChart.setType(Nightcharts::Pie);//{Histogramm,Pie,DPie};
    amountChart.setLegendType(Nightcharts::Round);//{Round,Vertical}
    amountChart.setCords(i1Left,40,width,height);
    amountChart.addPiece(tr("Кол-во"), i1Color,100);
    amountChart.draw(&painter);
    //amountChart.drawLegend(&painter);

    sumChart.setType(Nightcharts::Pie);//{Histogramm,Pie,DPie};
    sumChart.setLegendType(Nightcharts::Round);//{Round,Vertical}
    sumChart.setCords(i2Left,40,width,height);
    sumChart.addPiece(tr("Сумма"),i2Color,100);
    sumChart.draw(&painter);
    //sumChart.drawLegend(&painter);

    cashChart.setType(Nightcharts::Pie);//{Histogramm,Pie,DPie};
    cashChart.setLegendType(Nightcharts::Round);//{Round,Vertical}
    cashChart.setCords(i3Left,40,width,height);
    cashChart.addPiece("Выручка",i3Color,100);
    cashChart.draw(&painter);
}

void MainWindow::updateView()
{        
    // update current username    
    setWindowTitle("OrdersVi " + settings->getUserName());

    // update indicators
    ui->lcdAmount->display(indicatorsModel.getAmountPersent());
    ui->lcdSum->display(indicatorsModel.getSumPersent());
    ui->lcdCash->display(indicatorsModel.getCashPersent());

    // update tray
    trayIcon.setToolTip(tr("Текущий пользователь: ") + settings->getUserName() + "\n" +
                        tr("Кол-во: ") + QString::number(indicatorsModel.getAmount()) + "\n" +
                        tr("Сумма: ") + QString::number(indicatorsModel.getSum()) + "\n" +
                        tr("Выручка: ") + QString::number(indicatorsModel.getCash()));


    // обновим всю форму, чтобы перерисовались диаграммы
    repaint();
}

void MainWindow::updateModel()
{
    statusBar()->showMessage(tr("Получение данных..."));

    indicatorsModel = accessReader->getData();

    updateView();

    statusBar()->clearMessage();
}

void MainWindow::actionLogin_triggered()
{
    LoginDialog loginView(this);
    if (loginView.showDialog(settings, accessReader) == QDialog::Accepted) {

        updateView();
    }
}

void MainWindow::actionSettings_triggered()
{
    SettingsView settingsView(this);
    settingsView.inject(settings, accessReader);
    settingsView.updateView();

    timer.stop();
    if (settingsView.exec() == QDialog::Accepted) {

        settings->setAlwaysOnTop(settingsView.isAlwaysOnTop());

        // always on top setting
        Qt::WindowFlags flags = this->windowFlags();
        if (settings->getAlwaysOnTop()) {
            this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
            this->show();
        } else {
            this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
            this->show();
        }

    }
    timer.start();
}

void MainWindow::aboutView_triggered()
{

}

void MainWindow::restoreAction_triggered()
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
    connect(loginAction, SIGNAL(triggered()), this, SLOT(actionLogin_triggered()));

    settingsAction = new QAction(tr("Настройки"), this);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(actionSettings_triggered()));

    aboutViewAction = new QAction(tr("О программе..."), this);
    connect(aboutViewAction, SIGNAL(triggered()), this, SLOT(aboutView_triggered()));

    restoreAction = new QAction(tr("Показать/Скрыть"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(restoreAction_triggered()));

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
        restoreAction_triggered();
        break;
    case QSystemTrayIcon::MiddleClick:

        break;
    default:
        ;
    }
}
