#ifndef PMS_H
#define PMS_H

#include <stdint.h>

class PMS {
private:
	int fd;						// 시리얼통신 정보
	uint8_t pms[32];			// PMS7003 센서값 배열
	int pm1, pm25, pm10;	// 극초미세먼지, 초미세먼지, 미세먼지 값
	uint16_t checkcode;			// PMS7003 Checkcode 값
public:
	PMS();
	void PMSReceive();
	int getPM();
};

#endif // !PMS_H
