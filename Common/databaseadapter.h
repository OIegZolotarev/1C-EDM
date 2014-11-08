#ifndef DATABASEADAPTER_H
#define DATABASEADAPTER_H

#include <QtSql>

typedef struct dbRef_s
{
    char tableName[10];
    char objectUID[22];
}dbRef;

typedef char dbGenericValue[64];

class DatabaseAdapter
{
    QSqlDatabase m_DataBaseConnection;
public:
    DatabaseAdapter();
    ~DatabaseAdapter();

};

extern DatabaseAdapter * g_DbAdapter;

#endif // DATABASEADAPTER_H
