#pragma once
#include "structs.h"

class sCar
{
public:
	sRect rect;
	eDirection dir;
	int speed;
	bool init = false;
public:
	sCar();
	virtual void move();
	sRect getFuturePos();
	bool needPassOtherCar(sCar* otherCar);
	virtual int getFuel() = 0;
	virtual void refill(int count) = 0;
};
