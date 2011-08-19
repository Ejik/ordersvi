#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "indicatorsmodel.h"
#include "accessreader.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateModel()));
    timer.start(1000);
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


void MainWindow::updateIndicators()
{
    ui->lcdAmount->display(indicatorsModel.getAmount());
    ui->lcdSum->display(indicatorsModel.getSum());
    ui->lcdCash->display(indicatorsModel.getCash());
}

void MainWindow::updateModel()
{
    statusBar()->showMessage(tr("Получение данных..."));

    indicatorsModel = accessReader->getData();
    updateIndicators();

    statusBar()->clearMessage();
}

void MainWindow::on_actionLogin_triggered()
{
    LoginDialog loginView;
    if (loginView.showDialog(settings, accessReader) == QDialog::Accepted) {

        updateIndicators();
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionSettings_triggered()
{

}
