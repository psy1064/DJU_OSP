#ifndef PROCESS_H
#define PROCESS_H
#include "dht.h"
#include "pms.h"

class PROCESS {
private:
	DHT dht;
	PMS pms;
public:
	PROCESS();
	void processCycle();
	void printData();
};

void humanInterrupt();
void signal_handler(int signo);
void call_exitfunc();

#endif // !PROCESS_H
