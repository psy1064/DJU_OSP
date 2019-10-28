
#include "process.h"

#include <cstdlib>
#include <signal.h>
#include <wiringPi.h>
#include <iostream>

#define HUMAN 1			// Human detect sensor wPi Pin 1, BGM 18
#define LED_G 2			// LED wPi pin 2, BGM 2 7
#define LED_R 3

using namespace std;
unsigned char exit_flag = 0;

PROCESS::PROCESS()
{
    system("sudo motion");			// Motion 실행
    cout << "CCTV Enable" << endl;

    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);			// LED 핀 초기화
    pinMode(HUMAN, INPUT);			// 인체감지센서 초기화

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);		// 강제 종료 시 처리되는 인터럽트 처리

    atexit(call_exitfunc);			// 시스템 종료 시 호출되는 함수 선언

    if (wiringPiISR(HUMAN, INT_EDGE_RISING, &humanInterrupt) < 0)
    {
        exit(1);
    }						// 인체감지센서 인터럽트 선언 감지 시 humanInterrput 함수 실행
    else std::cout << "Interrupt enabled\n";
}
void PROCESS::processCycle()
{
    dht.DHTProcess();
    pms.PMSReceive();
    printData();
} // 데이터 수집
void PROCESS::printData()
{
    cout << "============================" << endl;
    cout << "hum = " << dht.getHum() << " temp = " << dht.getTemp() << endl;
    cout << "PM1 = " << pms.getPM() << endl;
    cout << "============================" << endl;
}
void PROCESS::putData(int h, int t, int d)
{
    h = dht.getHum();
    t = dht.getTemp();
    d = pms.getPM();
}
void humanInterrupt()
{
    cout << "Human detect" << endl;
}

void signal_handler(int signo)
{
    cout << "call signal handler" << endl;
    system("sudo killall -15 motion");
    exit_flag = 1;
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_R, HIGH);

    exit(0);
}

void call_exitfunc()
{
    cout << "call_ateixt func" << endl;
    if (exit_flag == 0)
    {
        system("sudo killall -15 motion");
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_R, HIGH);
    }
    cout << "CCTV disabled" << endl;
} // 시스템 종료 시 호출되는 함수
