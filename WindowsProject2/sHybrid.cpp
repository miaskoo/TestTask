#include "sHybrid.h"

sHybrid::sHybrid() : sElectroCar(), sGasCar() {};

void sHybrid::refill(int count) { charge += count / 2; fuel += count / 2; }
int sHybrid::getFuel() { return charge + fuel; }

void sHybrid::move() 
{
	if (rand() % 2 == 0)
	{
		charge--;
	}
	else
	{
		fuel--;
	}
	sCar::move();
}