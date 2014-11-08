#include "dbregtoolwindow.h"
#include <QApplication>
#include "../Common/databaseadapter.h"

DatabaseAdapter * g_DbAdapter;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DbRegToolWindow w;
    w.show();



    return a.exec();
}
