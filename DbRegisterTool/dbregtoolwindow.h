#ifndef DBREGTOOLWINDOW_H
#define DBREGTOOLWINDOW_H

#include <QDialog.h>

namespace Ui {
class DbRegToolWindow;
}

class DbRegToolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DbRegToolWindow(QWidget *parent = 0);
    ~DbRegToolWindow();

private:
    Ui::DbRegToolWindow *ui;
public Q_SLOTS:
    void addClientClick();
};

#endif // DBREGTOOLWINDOW_H
