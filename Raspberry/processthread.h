#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>

#include "process.h"

class processThread : public QThread
{
    Q_OBJECT
public:
    explicit processThread(QObject *parent = 0);

private:
    PROCESS process;
    void run();
signals:
    void setValue(int temp, int hum, int dust);



};

#endif // PROCESSTHREAD_H
