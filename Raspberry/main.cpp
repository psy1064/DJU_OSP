#include "mainwindow.h"
#include "process.h"
#include "widget.h"

#include <QApplication>
#include <wiringPi.h>
#include <iostream>
#include <pthread.h>
#include <QString>

#define DELAY 5000		// Delay 5초 
#define HUMAN 1			// Human detect sensor wPi Pin 1

PROCESS process;

void* loopFunction(void* num)
{
    int hum;
    int temp;
    int dust;
    Widget widget;
    while (1)
    {
        widget.show();			// Qt display
        process.processCycle();		// 데이터 수집
        process.putData(hum, temp, dust);
        delay(DELAY);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);		// QApplication 생성
    /*Widget widget;
    widget.show();*/

    pthread_t loopThread;		// 데이터 수집 및 Qt 출력 쓰레드
    pthread_create(&loopThread, NULL, loopFunction, NULL);

    return a.exec();
}

