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
    } // ½Ã¸®¾ó Åë½Å ÃÊ±âÈ­
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
}
int PMS::getPM()
{
    return pm1;
}
