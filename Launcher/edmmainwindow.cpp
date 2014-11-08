#include "edmmainwindow.h"
#include "ui_edmmainwindow.h"

EDMMainWindow::EDMMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EDMMainWindow)
{
    ui->setupUi(this);
}

EDMMainWindow::~EDMMainWindow()
{
    delete ui;
}
