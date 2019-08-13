#include<iostream>
#include<cstdio>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<wiringPi.h>
#include<wiringSerial.h>

#define DHT11 0				// DHT11 wPi Pin 0
#define HUMAN 1				// Human detect sensor wPi Pin 1
#define LED 2				// LED wPi pin 2

using namespace std;

unsigned char exit_flag = 0;

class Project {
private:
	uint8_t dhtData[5];		// DHT11 센서값 배열
	int hum, temp;			// 습도, 온도

	int fd;						// 시리얼통신 정보
	uint8_t pms[32];			// PMS7003 센서값 배열
	uint16_t pm1, pm25, pm10;	// 극초미세먼지, 초미세먼지, 미세먼지 값
	uint16_t checkcode;			// PMS7003 Checkcode 값

public:
	Project();
	// Constructor
	~Project();
	void DHTProcess();
	void DHTSend();
	void DHTResponse();
	bool DHTGetDate();
	// DHT11 method
	void PMSRecive();
	// PMS7003 method
	void ProjectProcess();
	void PrintData();
	// Whole Process method
};

Project::Project()
{
	system("sudo motion");		// Motion Enable
	cout << "CCTV Enable" << endl;
	hum = temp = 0;
	for (int i = 0; i < 5; i++)
	{
		dhtData[i] = 0;
	}

	if ((fd = serialOpen("/dev/ttyUSB0", 9600)) < 0)
	{
		fprintf(stderr, "Unable serial", strerror(errno));
		exit(1);
	} // 시리얼 통신 초기화

	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);
}
Project::~Project()
{
	system("killall -9 motion");
	cout << "CCTV disabled" << endl;
	digitalWrite(LED, LOW);
}
void Project::DHTProcess()
{
	DHTSend();
	DHTResponse();
	bool tmp = DHTGetDate();
} // DHT11 센서 측정 함수
void Project::DHTSend()
{
	pinMode(DHT11, OUTPUT);
	digitalWrite(DHT11, LOW);
	delay(20);
	digitalWrite(DHT11, HIGH);
	delayMicroseconds(30);
}
void Project::DHTResponse()
{
	pinMode(DHT11, INPUT);

	while (digitalRead(DHT11) != LOW);
	while (digitalRead(DHT11) != HIGH);
	while (digitalRead(DHT11) != LOW);
}
bool Project::DHTGetDate()
{
	int count = 0;
	int j;
	for (j = 0; j < 40; j++)
	{
		count = 0;
		while (digitalRead(DHT11) == LOW)
		{
			delayMicroseconds(1);
			count++;
			if (count >= 255) return false; 	// start to transmit 1-bit data(50us)
		} // When DHT is sending data to MCU, every bit of data begins with the 50us low-voltage-level
		count = 0;
		while (digitalRead(DHT11) == HIGH)
		{
			delayMicroseconds(1);
			count++;
			if (count >= 255) return false;
		}
		dhtData[j / 8] <<= 1;
		if (count > 30)
		{
			dhtData[j / 8] |= 1;
		}
	}
	if ((j >= 40) && (dhtData[4] == dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]))
	{
		hum = (int)dhtData[0];
		temp = (int)dhtData[2];
		cout << "DHT11 Right" << endl;
		return true;
	}
	else
	{
		return false;
	}
}
void Project::PMSRecive()
{
	for (int i = 0; i < 32; i++)
	{
		pms[i] = serialGetchar(fd);
		if (i < 30)
			checkcode += pms[i];
	}
	if ((pms[0] == 0x42) && (pms[1] == 0x4d))
	{
		uint16_t tmp = (pms[30] << 8) + pms[31];
		if (checkcode == tmp)	cout << "PMS7003 Right" << endl;

		pm1 = (pms[10] << 8) + pms[11];
		pm25 = (pms[12] << 8) + pms[13];
		pm10 = (pms[14] << 8) + pms[15];

		checkcode = 0;
	}
}
void Project::PrintData()
{
	cout << "============================" << endl;
	cout << "hum = " << hum << " temp = " << temp << endl;
	cout << "PM1 = " << pm1 << " PM2.5 = " << pm25 << " PM10 = " << pm10 << endl;
	cout << "============================" << endl;
}
void Project::ProjectProcess()
{
	DHTProcess();
	PMSRecive();
	PrintData();
}
void signal_handler(int signo)
{
	cout << "call signal handler" << endl;
	system("sudo killall -15 motion");
	exit_flag = 1;
	digitalWrite(LED, LOW);
	exit(0);
}
void call_exitfunc()
{
	cout << "call_ateixt func" << endl;
	if (exit_flag == 0)
	{
		system("sudo killall -15 motion");
		digitalWrite(LED, LOW);
	}

	cout << "CCTV disabled" << endl;
}
int main()
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	atexit(call_exitfunc);

	if (wiringPiSetup() == -1)
	{
		cout << "wiringPiSetup가 설치되지 않았습니다." << endl;
		exit(1);
	}

	Project project;

	while (1)
	{
		project.ProjectProcess();
		delay(3000);
	}
}
