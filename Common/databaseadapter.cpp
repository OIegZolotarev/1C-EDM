
#include "databaseadapter.h"


DatabaseAdapter::DatabaseAdapter()
{
     m_DataBaseConnection = QSqlDatabase::addDatabase("QSQLITE");

     QString str = QFileInfo( QCoreApplication::applicationFilePath() ).dir().path();
     m_DataBaseConnection.setDatabaseName(str + "/database.db");
     m_DataBaseConnection.open();

     QSqlQuery q("INSERT INTO CLIENTS VALUES(\"Olololo\",\"Шапландия \")",m_DataBaseConnection);

     q.exec();
}

DatabaseAdapter::~DatabaseAdapter()
{

}
