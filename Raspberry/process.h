#ifndef PROCESS_H
#define PROCESS_H
#include "dht.h"
#include "pms.h"
#include <QApplication>
#include <QLabel>

class PROCESS {
private:
	DHT dht;
	PMS pms;
    //QLabel* temp, hum, dust;
public:
	PROCESS();
	void processCycle();
	void printData();
    void putData(int h, int t, int d);
};

void humanInterrupt();
void signal_handler(int signo);
void call_exitfunc();

#endif // !PROCESS_H
