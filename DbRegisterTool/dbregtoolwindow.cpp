#include "dbregtoolwindow.h"
#include "ui_dbregtoolwindow.h"
#include "addclientprojectdialog.h"

DbRegToolWindow::DbRegToolWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbRegToolWindow)
{
    ui->setupUi(this);
    setFixedSize(width(),height());

}

DbRegToolWindow::~DbRegToolWindow()
{
    delete ui;
}

void DbRegToolWindow::addClientClick()
{
   AddClientProjectDialog * dialog = new AddClientProjectDialog(this);
    dialog->setWindowModality(Qt::WindowModal);
   dialog->exec();

   delete dialog;

}
