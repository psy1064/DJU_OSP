#include "process.h"
#include <wiringPi.h>
#include <iostream>
#include <signal.h>

#define DELAY 5000		// Delay 5√ 
#define HUMAN 1			// Human detect sensor wPi Pin 1, BGM 18

int main()
{
	PROCESS process;

	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	atexit(call_exitfunc);

	if (wiringPiISR(HUMAN, INT_EDGE_RISING, &humanInterrupt) < 0)
	{
		exit(1);
	}
	else std::cout << "Interrupt enabled\n";

	while (1)
	{
		process.processCycle();
		delay(DELAY);
	}
}