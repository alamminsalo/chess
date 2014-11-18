#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "startexternal.h"
#include "dbconnector.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    qmlRegisterType<StartExternal>("StartExternal", 1, 0, "StartExternal");
    qmlRegisterType<DBConnector>("SqlConnector", 1, 0, "SqlConnector");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Loader.qml")));

    return app.exec();
}
