#include "process.h"

#include <cstdlib>
#include <wiringPi.h>
#include <iostream>

#define HUMAN 1			// Human detect sensor wPi Pin 1, BGM 18
#define LED_G 2			// LED wPi pin 2, BGM 2 7
#define LED_R 3

using namespace std;
unsigned char exit_flag = 0;

PROCESS::PROCESS()
{
	system("sudo motion");			// Motion Enable
	cout << "CCTV Enable" << endl;

	pinMode(LED_G, OUTPUT);
	pinMode(LED_R, OUTPUT);
	pinMode(HUMAN, INPUT);

	digitalWrite(LED_R, LOW);
	digitalWrite(LED_G, HIGH);
}
void PROCESS::processCycle()
{
	dht.DHTProcess();
	pms.PMSReceive();
	printData();
}
void PROCESS::printData()
{
	cout << "============================" << endl;
	cout << "hum = " << dht.getHum() << " temp = " << dht.getTemp() << endl;
	cout << "PM1 = " << pms.getPM() << endl;
	cout << "============================" << endl;
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