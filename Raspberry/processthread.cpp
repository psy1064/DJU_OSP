#include "processthread.h"
#include "process.h"
#include "dialog.h"
processThread::processThread(QObject *parent) : QThread(parent)
{

}
void processThread::run()
{
    int t, h, d;
    while(1)
    {
        process.processCycle();
        process.putData(&t, &h, &d);
        emit setValue(t, h, d);
        sleep(3);
    }

}
