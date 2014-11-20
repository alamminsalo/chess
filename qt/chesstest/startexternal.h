#ifndef STARTEXTERNAL_H
#define STARTEXTERNAL_H

#include <QObject>
#include <QProcess>

class StartExternal : public QObject
{
    Q_OBJECT

    QProcess *process;
public:
    explicit StartExternal(QObject *parent = 0);

signals:

public slots:
    void start();
    void start(QStringList);
    void kill();

};

#endif // STARTEXTERNAL_H
