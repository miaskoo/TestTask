#include "sElectroCar.h"

sElectroCar::sElectroCar() : sCar() { charge = 0; };

int sElectroCar::getFuel() { return charge; }
void sElectroCar::refill(int count) { charge += count; }
void sElectroCar::move() { charge--; sCar::move(); }