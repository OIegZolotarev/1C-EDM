#include "edmmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EDMMainWindow w;
    w.show();

    return a.exec();
}
