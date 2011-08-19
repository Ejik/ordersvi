#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "indicatorsmodel.h"
#include "accessreader.h"

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

}


void MainWindow::on_actionLogin_triggered()
{
    AccessReader reader;
    IndicatorsModel model = reader.getData();

    ui->lcdAmount->display(model.getAmount());
    ui->lcdSum->display(model.getSum());
    ui->lcdCash->display(model.getCash());
}

