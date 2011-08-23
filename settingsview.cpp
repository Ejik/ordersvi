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


    tableModel.setTable("Norms");
    tableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel.select();

    ui->normsTableView->setModel(&tableModel);

    ui->normsTableView->setColumnHidden(0, true);
    ui->normsTableView->setColumnWidth(1, 200);
    for (int i = 2; i < tableModel.columnCount(); i++) {
        ui->normsTableView->setColumnWidth(i, 70);
    }

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
   ui->alwaysOnTopBox->setChecked(settings->getAlwaysOnTop());
   ui->autostartApplicationBox->setChecked(settings->getAutoStartApplication());
}

bool SettingsView::isAlwaysOnTop()
{
    return ui->alwaysOnTopBox->isChecked();
}

bool SettingsView::isAutostartApplication()
{
    return ui->autostartApplicationBox->isChecked();
}
