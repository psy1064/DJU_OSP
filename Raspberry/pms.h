#ifndef PMS_H
#define PMS_H

#include <stdint.h>

class PMS {
private:
    int fd;						// ï¿œÃžï¿œï¿œï¿œï¿œï¿œï¿œï¿œ ï¿œï¿œï¿œï¿œ
    uint8_t pms[32];			// PMS7003 ï¿œï¿œï¿œï¿œï¿œï¿œ ï¿œè¿­
    int pm1, pm25, pm10;	// ï¿œï¿œï¿œÊ¹ÌŒï¿œï¿œï¿œï¿œï¿œ, ï¿œÊ¹ÌŒï¿œï¿œï¿œï¿œï¿œ, ï¿œÌŒï¿œï¿œï¿œï¿œï¿œ ï¿œï¿œ
    uint16_t checkcode;			// PMS7003 Checkcode ï¿œï¿œ
public:
    PMS();
    void PMSReceive();
    int getPM();
};

#endif // PMS_H
