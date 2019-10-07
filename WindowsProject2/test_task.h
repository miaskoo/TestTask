#pragma once
//FUNC
sCar* spawnCarFromPos(int);
sCar *spawnRandomCarFromRandomPos();
bool setCarRandomPos(sCar*);
bool setCarPos(int, sCar*);
bool Init_Pull();//инитим машины в пул
bool logic_tick();//проигрывается логика машинок на один тик
//END FUNC