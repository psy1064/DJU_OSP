\#ifndef DHT_H
#define DHT_H

#include <stdint.h>

class DHT {
private:
    uint8_t dhtData[5];		// DHT11 측정 데이터 저장하는 배열
    int hum, temp;		// 측정한 온도, 습도 값
public:
    DHT();
    void DHTProcess();		// DHT11 센서 데이터 수집 싸이클
    void DHTSend();		// DHT11에게 수신 준비를 알리는 함수
    void DHTResponse();		// DHT11이 사용자에게 송신 준비를 알리는 함수
    bool DHTGetDate();		// DHT11에서 데이터를 받아오는 함수
    int getTemp();		// 측정한 온도 데이터 반환
    int getHum();		// 측정한 습도 데이터 반환
};

#endif // DHT_H
