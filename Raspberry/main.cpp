#include "mainwindow.h"
#include "process.h"
#include "widget.h"

#include <QApplication>
#include <wiringPi.h>
#include <iostream>
#include <pthread.h>
#include <QString>

#define DELAY 5000		// Delay 5ÃÊ
#define HUMAN 1			// Human detect sensor wPi Pin 1, BGM 18

PROCESS process;

void* loopFunction(void* num)
{
    int hum;
    int temp;
    int dust;
    Widget widget;
    while (1)
    {
        widget.show();
        process.processCycle();
        process.putData(hum, temp, dust);
        widget.setData(hum, temp, dust);
        delay(DELAY);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*Widget widget;
    widget.show();*/

    pthread_t loopThread;
    pthread_create(&loopThread, NULL, loopFunction, NULL);

    return a.exec();
}

