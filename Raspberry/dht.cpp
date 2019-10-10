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
    }
    else std::cout << "wiringPiSetup\n";
}
void DHT::DHTProcess()
{
    DHTSend();
    DHTResponse();
    bool tmp = DHTGetDate();
} // DHT11 ¼¾¼­ ÃøÁ¤ ÇÔ¼ö
void DHT::DHTSend()
{
    pinMode(DHT11, OUTPUT);
    digitalWrite(DHT11, LOW);
    delay(20);
    digitalWrite(DHT11, HIGH);
    delayMicroseconds(30);
}
void DHT::DHTResponse()
{
    pinMode(DHT11, INPUT);

    while (digitalRead(DHT11) != LOW);
    while (digitalRead(DHT11) != HIGH);
    while (digitalRead(DHT11) != LOW);
}
bool DHT::DHTGetDate()
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
        std::cout << "DHT11 Right\n";
        return true;
    }
    else
    {
        return false;
    }
}
int DHT::getTemp()
{
    return temp;
}
int DHT::getHum()
{
    return hum;
}
