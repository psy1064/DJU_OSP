#include<iostream>
#include<wiringPi.h>

#define HUMAN 1

using namespace std;

void humanInterrupt() 
{
	cout << "human" << endl;
}
int main()
{
	if (wiringPiSetup() == -1)
		exit(1);

	pinMode(HUMAN, INPUT);

	if (wiringPiISR(HUMAN, INT_EDGE_RISING, &humanInterrupt) < 0)
	{
		return 1;
	}

	while (1)
	{
		
	}
}