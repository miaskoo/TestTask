#include "sGasEngine.h"


sGasCar::sGasCar() : sCar() {fuel = 0;};

int sGasCar::getFuel() { return fuel; }
void sGasCar::refill(int count) { fuel += count; }
void sGasCar::move() { fuel--; sCar::move(); }