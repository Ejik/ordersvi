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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bindObjects(SettingsModel *settings, AccessReader *accessReader)
{
    this->settings = settings;
    this->accessReader = accessReader;
}


void MainWindow::on_actionLogin_triggered()
{
    LoginDialog loginView;
    if (loginView.showDialog(settings, accessReader) == QDialog::Accepted) {

        IndicatorsModel model = accessReader->getData();

        ui->lcdAmount->display(model.getAmount());
        ui->lcdSum->display(model.getSum());
        ui->lcdCash->display(model.getCash());
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
