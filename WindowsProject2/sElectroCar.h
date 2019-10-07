#pragma once
#include "sCar.h"
class sElectroCar : public virtual sCar {
protected:
	int charge;

public:
	sElectroCar();

	int getFuel();
	void refill(int count);
	virtual void move() override;

};
