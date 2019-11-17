#include "processthread.h"
#include "process.h"
#include "dialog.h"

#include <iostream>
processThread::processThread(QObject *parent) : QThread(parent)
{

}
void processThread::run()
{
    std::cout << "thread start\n";

    int t = 0, h = 0, d = 0;
    while(1)
    {
        process.processCycle();
        process.putData(&t, &h, &d);
        while(t == 0)
        {
            sleep(2);
            process.processCycle();
            process.putData(&t, &h, &d);
        }
        emit setValue(t, h, d);
        sleep(10);
    }
}

