#include "dht.h"
#include <wiringPi.h>
#include <iostream>

#define DHT11 0

DHT::DHT()
{
    hum = temp = 0;
    for (int i = 0; i < 5; i++)
    {
        dhtData[i] = 0;
    }
    if (wiringPiSetup() == -1)
    {
        std::cout << "wiringPiSetup Error\n";
        exit(1);
    } // wiringPiSetup
    else std::cout << "wiringPiSetup\n";
} // DHT11 센서 데이터 수집 클래스 생성자
void DHT::DHTProcess()
{
    std::cout << "DHT11 Start\n";
    DHTSend();
    DHTResponse();
    DHTGetData();
} // DHT11 센서 데이터 수집 싸이클
void DHT::DHTSend()
{
    std::cout << "DHTSend\n";
    pinMode(DHT11, OUTPUT);
    digitalWrite(DHT11, LOW);
    delay(20);
    digitalWrite(DHT11, HIGH);
    delayMicroseconds(30);
} // DHT11에게 수신 준비를 알리는 함수
void DHT::DHTResponse()
{
    std::cout << "DHTResponse";
    char count = 0;
    pinMode(DHT11, INPUT);
    std::cout << '.';
    while (digitalRead(DHT11) != LOW)
    {
        delayMicroseconds(1);
        if(count++ >= 255)
        {
            count = 0;
            std::cout << "break1";
            break;
        }
    }
    std::cout << '.';
    while (digitalRead(DHT11) != HIGH)
    {
        delayMicroseconds(1);
        if(count++ >= 255)
        {
            std::cout << "break2";
            break;
        }
    }
    std::cout << ".\n";
    while (digitalRead(DHT11) != LOW);
} // DHT11이 사용자에게 송신 준비를 알리는 함수
bool DHT::DHTGetData()
{
    std::cout << "DHTGetData\n";
    char count = 0;
    int j;
    for (j = 0; j < 40; j++)
    {
        count = 0;
        while (digitalRead(DHT11) == LOW)
        {
            delayMicroseconds(1);
            count++;
            if (count >= 255)
            {
                std::cout << "break1\n";
                return false;
            }
        } // 일정 시간이 지나면 false 리턴
        count = 0;
        while (digitalRead(DHT11) == HIGH)
        {
            delayMicroseconds(1);
            count++;
            if (count >= 255)
            {
                std::cout << "break2\n";
                return false;
            }
        } // 일정 시간이 지나면 false 리턴
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
        std::cout << "DHT11 Right\n";
        return true;
    } // 마지막 8개 비트와 나머지 32개의 비트의 합이 같아야 함
    else
    {
        std::cout << "break3\n";
        return false;
    }
} // DHT11에서 데이터를 받아오는 함수
int DHT::getTemp()
{
    return temp;
} // 측정한 온도 데이터 반환
int DHT::getHum()
{
    return hum;
} // 측정한 습도 데이터 반환
