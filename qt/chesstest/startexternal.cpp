#include "startexternal.h"
#include <QApplication>
#include <iostream>


StartExternal::StartExternal(QObject *parent) :
    QObject(parent)
{
    process = new QProcess(qApp);
}

void StartExternal::start(QStringList args){
    std::cout << "Arguments: "+args.first().toStdString() << std::endl;
    QString url = "./sfml-app";
    if(process->startDetached(url,args))
        std::cout << "Success!\n";
}

void StartExternal::kill(){
    process->kill();
}
