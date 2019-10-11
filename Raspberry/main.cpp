#include "mainwindow.h"
#include "process.h"

#include <QApplication>
#include <wiringPi.h>
#include <iostream>
#include <signal.h>
#include <pthread.h>

#define DELAY 5000		// Delay 5ÃÊ
#define HUMAN 1			// Human detect sensor wPi Pin 1, BGM 18

PROCESS process;

void* loopFunction(void* num)
{
    while (1)
    {
        process.processCycle();
        delay(DELAY);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    pthread_t loopThread;

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    atexit(call_exitfunc);

    if (wiringPiISR(HUMAN, INT_EDGE_RISING, &humanInterrupt) < 0)
    {
        exit(1);
    }
    else std::cout << "Interrupt enabled\n";

    pthread_create(&loopThread, NULL, loopFunction, NULL);
    //pthread_join(loopThread,NULL);

    return a.exec();
}

