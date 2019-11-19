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
    int count;
public:
	PROCESS();
	void processCycle();
	void printData();
    void putData(int* t, int* h, int* d);
};

void signal_handler(int signo);
void call_exitfunc();

#endif // !PROCESS_H
