#ifndef ADDCLIENTPROJECTDIALOG_H
#define ADDCLIENTPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddClientProjectDialog;
}

class AddClientProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientProjectDialog(QWidget *parent = 0);
    ~AddClientProjectDialog();

private:
    Ui::AddClientProjectDialog *ui;
public Q_SLOTS:
    void onOk();
    void onCancel();
};

#endif // ADDCLIENTPROJECTDIALOG_H
