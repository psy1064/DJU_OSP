#include "process.h"

#include <cstdlib>
#include <signal.h>
#include <wiringPi.h>
#include <iostream>

#define HUMAN 2			// Human detect sensor wPi Pin 2

using namespace std;
unsigned char exit_flag = 0;

PROCESS::PROCESS()
{
    system("sudo motion");			// Motion 실행
    cout << "CCTV Enable" << endl;

    pinMode(HUMAN, INPUT);			// 인체감지센서 초기화

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);		// 강제 종료 시 처리되는 인터럽트 처리

    atexit(call_exitfunc);			// 시스템 종료 시 호출되는 함수 선언
}
PROCESS::~PROCESS()
{
    system("sudo killall -15 motion");
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
    cout << "temp = " << dht.getTemp() << " hum = " << dht.getHum() << endl;
    cout << "PM10 = " << pms.getPM() << endl;
    cout << "============================" << endl;
}
void PROCESS::putData(int* temp, int* hum, int* dust, int* human)
{
    *temp = dht.getTemp();
    *hum = dht.getHum();
    *dust = pms.getPM();
    *human = digitalRead(HUMAN);
}
void signal_handler(int signo)
{
    cout << "call signal handler" << endl;
    system("sudo killall -15 motion");
    exit_flag = 1;

    exit(0);
}

void call_exitfunc()
{
    cout << "call_ateixt func" << endl;
    if (exit_flag == 0)     system("sudo killall -15 motion");
    cout << "CCTV disabled" << endl;
} // 시스템 종료 시 호출되는 함수
