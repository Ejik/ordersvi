#include <QDebug>
#include "settingsview.h"
#include "ui_settingsview.h"


SettingsView::SettingsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsView)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), &tableModel, SLOT(submitAll()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


}

SettingsView::~SettingsView()
{
    delete ui;
}

void SettingsView::inject(SettingsModel *settings, AccessReader *accessReader)
{
    this->accessReader = accessReader;
    this->settings = settings;
}


void SettingsView::updateView()
{
    updateNormsTable();
   ui->alwaysOnTopBox->setChecked(settings->alwaysOnTop());
   ui->autostartApplicationBox->setChecked(settings->getAutoStartApplication());
}

void SettingsView::updateNormsTable()
{
    QString filter = "USERID = '" + settings->userID() + "'";

    tableModel.setTable("Norms");
    tableModel.setFilter(filter);
    tableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel.select();

    ui->normsTableView->setModel(&tableModel);

    ui->normsTableView->setColumnHidden(0, true);
    ui->normsTableView->setColumnHidden(14, true);
    ui->normsTableView->setColumnWidth(1, 200);
    for (int i = 2; i < tableModel.columnCount(); i++) {
        ui->normsTableView->setColumnWidth(i, 70);
    }
}

bool SettingsView::isAlwaysOnTop()
{
    return ui->alwaysOnTopBox->isChecked();
}

bool SettingsView::isAutostartApplication()
{
    return ui->autostartApplicationBox->isChecked();
}
