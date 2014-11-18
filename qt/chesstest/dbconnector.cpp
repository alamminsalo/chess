#include "dbconnector.h"

DBConnector::DBConnector(QObject *parent) :
    QObject(parent)
{
}

bool DBConnector::connectToDatabase(QString host, QString database, QString username, QString password)
{
    db = QSqlDatabase::addDatabase("QMYSQL","conn1");
    db.setHostName(host);
    db.setDatabaseName(database);
    db.setUserName(username);
    db.setPassword(password);
    return db.open();
}

bool DBConnector::showTable(QString tablename)
{
    QSqlQuery query;
    query.exec("SELECT * from "+tablename+";");

    while (query.next()){

    }
}
