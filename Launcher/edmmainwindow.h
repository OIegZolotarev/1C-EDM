#ifndef EDMMAINWINDOW_H
#define EDMMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class EDMMainWindow;
}

class EDMMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EDMMainWindow(QWidget *parent = 0);
    ~EDMMainWindow();

private:
    Ui::EDMMainWindow *ui;
};

#endif // EDMMAINWINDOW_H
