#pragma once
//FUNC
sCar* spawnCarFromPos(int);
sCar *spawnRandomCarFromRandomPos();
bool setCarRandomPos(sCar*);
bool setCarPos(int, sCar*);
bool Init_Pull();//������ ������ � ���
bool logic_tick();//������������� ������ ������� �� ���� ���
//END FUNC