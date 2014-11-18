#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class DBConnector : public QObject
{
    Q_OBJECT
protected:
    QSqlDatabase db;

public:
    explicit DBConnector(QObject *parent = 0);

signals:

public slots:
    bool connectToDatabase ( QString host, QString database, QString username, QString password );
    bool showTable(QString tablename);
};

#endif // DBCONNECTOR_H
