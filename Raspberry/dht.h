#ifndef DHT_H
#define DHT_H

#include <stdint.h>

class DHT {
private:
    uint8_t dhtData[5];			// DHT11 ï¿œï¿œï¿œï¿œï¿œï¿œ ï¿œè¿­
    int hum, temp;				// ï¿œï¿œï¿œï¿œ, ï¿œÂµï¿œ
public:
    DHT();
    void DHTProcess();
    void DHTSend();
    void DHTResponse();
    bool DHTGetDate();
    int getTemp();
    int getHum();
};

#endif // DHT_H
