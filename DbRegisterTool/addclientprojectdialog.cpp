#include "addclientprojectdialog.h"
#include "ui_addclientprojectdialog.h"
#include "../common/databaseadapter.h"

AddClientProjectDialog::AddClientProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientProjectDialog)
{
    ui->setupUi(this);
}

AddClientProjectDialog::~AddClientProjectDialog()
{
    delete ui;
}

void AddClientProjectDialog::onOk()
{
    QSqlQuery * addQuery = new QSqlQuery("INSERT INTO CLIENT VALUES(:")
}

void AddClientProjectDialog::onCancel()
{

}
