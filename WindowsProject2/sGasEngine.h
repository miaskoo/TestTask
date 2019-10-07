#pragma once
#include "sCar.h"

class sGasCar : public virtual  sCar
{
protected:
	int fuel;

public:
	sGasCar();

	int getFuel();
	void refill(int count);
	virtual void move() override;

};