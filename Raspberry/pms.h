#ifndef PMS_H
#define PMS_H

#include <stdint.h>

class PMS {
private:
    int fd;
    uint8_t pms[32];		// PMS7003 데이터 수집 배열
    int pm1, pm25, pm10;	// 미세먼지 단위
    uint16_t checkcode;		// PMS7003 Checksum code
public:
    PMS();
    void PMSReceive();		// PMS7003에서 데이터를 받아오는 함수
    int getPM();		// 미세먼지(PM10) 데이터 반환
};

#endif // PMS_H
