#pragma once
#include "sElectroCar.h"
#include "sGasEngine.h"
class sHybrid : public sGasCar, public sElectroCar
{
public:
	sHybrid();

	void refill(int count);
	int getFuel();
	void move();
};
