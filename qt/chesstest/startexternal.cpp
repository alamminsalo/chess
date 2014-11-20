#include "startexternal.h"
#include <QApplication>
#include <iostream>


StartExternal::StartExternal(QObject *parent) :
    QObject(parent)
{
    process = new QProcess(qApp);
}

void StartExternal::start(QStringList args){
    std::cout << "Arguments: "+args.first().toStdString() << args.last().toStdString() << std::endl;
    QString url = "./sfml-app";
    if (process->startDetached(url,args))
        std::cout << "Success!\n";
}

void StartExternal::start(){
    std::cout << "Starting with no args..\n";
    QString url = "./sfml-app";
    if (process->startDetached(url))
        std::cout << "Success!\n";
}

void StartExternal::kill(){
    process->kill();
}
