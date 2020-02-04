#include "processthread.h"
#include "process.h"
#include "dialog.h"

#include <iostream>
processThread::processThread(QObject *parent) : QThread(parent)
{
    temp = hum = dust = human = 0;
    pre_temp = pre_hum = pre_dust = pre_human = 0;
}
void processThread::run()
{
    std::cout << "thread start\n";

    while(1)
    {
        process.processCycle();
        process.putData(&temp, &hum, &dust, &human);
        while(temp == 0)
        {
            sleep(2);
            process.processCycle();
            process.putData(&temp, &hum, &dust, &human);
        }

        if(temp - pre_temp != 0 || hum - pre_hum !=0 || dust - pre_dust != 0 || human - pre_human !=0)
        {
            pre_temp = temp;
            pre_hum = hum;
            pre_dust = dust;
            pre_human = human;
            std::cout << "change\n";
            emit setValue(temp, hum, dust, human);
        }
        sleep(5);
    }
}

