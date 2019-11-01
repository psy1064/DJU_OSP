#include "pms.h"
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <wiringPi.h>
#include <wiringSerial.h>

PMS::PMS()
{
    if ((fd = serialOpen("/dev/ttyUSB0", 9600)) < 0)
    {
        fprintf(stderr, "Unable serial", strerror(errno));
        exit(1);
    } // Serial 통신을 위한 연결
}
void PMS::PMSReceive()
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
        if (checkcode == tmp)	std::cout << "PMS7003 Right\n";

        pm1 = (pms[10] << 8) + pms[11];
        pm25 = (pms[12] << 8) + pms[13];
        pm10 = (pms[14] << 8) + pms[15];

        checkcode = 0;
    }
} // PMS7003에서 데이터를 받아오는 함수
int PMS::getPM()
{
    return pm10; // 미세먼지 데이터 반환
} // 미세먼지(PM10) 데이터 반환
