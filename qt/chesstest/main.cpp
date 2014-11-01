#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "startexternal.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<StartExternal>("StartExternal", 1, 0, "StartExternal");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Loader.qml")));

    return app.exec();
}
