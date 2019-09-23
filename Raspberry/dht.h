#ifndef DHT_H
#define DHT_H

#include <stdint.h>

class DHT {
private:
	uint8_t dhtData[5];			// DHT11 센서값 배열
	int hum, temp;				// 습도, 온도
public:
	DHT();
	void DHTProcess();
	void DHTSend();
	void DHTResponse();
	bool DHTGetDate();
	int getTemp();
	int getHum();
};
#endif