
//INCLUDE
#include "structs.h"

//classes cars
#include "sCar.h"
#include "sElectroCar.h"
#include "sGasEngine.h"
#include "sHybrid.h"

//H
#include "test_task.h"
//END INCLUDE


//DEFINE
#define MAX_POSITIONS 4//left, rigth, top, bot
#define POS_LEFT 0
#define POS_RIGTH 1
#define POS_TOP 2
#define POS_BOT 3
//END DEFINE


//VARIABLE
std::vector<sCar*> pull_cars;
const size_t initialCarsCount = 10;//переменная  отвечает за количество создаваемых машин

extern int sizeCarWidth;//эти переменные отвечают за размер машинок и находятся в main.cpp 
extern int sizeCarHeight;

extern int SCREEN_WIDTH;//эти переменные отвечают за размер экрана и находятся в main.cpp 
extern int SCREEN_HEIGHT;
//END VARIABLE


bool setCarPos(int type, sCar* car)
{
	if (car == nullptr)
		return false;
	switch (type)
	{
	case POS_RIGTH:
	{
		car->rect = sRect(SCREEN_WIDTH, SCREEN_HEIGHT / 2 + sizeCarHeight * 0.5, sizeCarWidth, sizeCarHeight - sizeCarHeight * 0.5);
		car->dir = eDirection::LEFT;
		break;
	}
	case POS_LEFT:
	{
		car->rect = sRect(0, SCREEN_HEIGHT / 2, sizeCarWidth, sizeCarHeight - sizeCarHeight*0.5);
		car->dir = eDirection::RIGHT;
		break;
	}
	case POS_BOT:
	{
		car->rect = sRect(SCREEN_WIDTH / 2, 0, sizeCarWidth - sizeCarWidth*0.5, sizeCarHeight);
		car->dir = eDirection::BOT;
		break;
	}
	case POS_TOP:
	{
		car->rect = sRect(SCREEN_WIDTH / 2 + sizeCarWidth * 0.5, SCREEN_HEIGHT, sizeCarWidth - sizeCarWidth * 0.5, sizeCarHeight);
		car->dir = eDirection::TOP;
		break;
	}
	default:
	{
		return false;
	}
	}
	return true;
}


sCar* spawnCarFromPos(int type_pos) 
{
	if (type_pos >= MAX_POSITIONS)
		return nullptr;//неизвестная позиция
	sCar* car = nullptr;
	int carTypeCount = 3;
	int carType = rand() % carTypeCount;
	switch (carType)
	{
	case 0:
	{
		car = new sGasCar();
		break;
	}
	case 1:
	{
		car = new sElectroCar();
		break;
	}
	case 2:
	{
		car = new sHybrid();
		break;
	}
	default:
	{
		return nullptr; //неизвестный тип
	}
	}
	if (setCarPos(type_pos, car) == false)
	{
		delete car;
		return nullptr;
	}

	car->speed = 1;
	car->init = true;
	return car;
}


sCar *spawnRandomCarFromRandomPos()
{
	return spawnCarFromPos(rand() % MAX_POSITIONS);
}

bool setCarRandomPos(sCar *car)
{
	return setCarPos(rand() % MAX_POSITIONS, car);
}




bool logic_tick()
{

	auto intersect_car([=](sCar *car) { return (car->rect.pos.x <= 0 || car->rect.pos.x >= SCREEN_WIDTH || car->rect.pos.y <= 0 || car->rect.pos.y >= SCREEN_HEIGHT); });

	for (auto car : pull_cars)
	{
		if (car->init == true)
		{

			bool stop = false;
			for (auto car2 : pull_cars)
			{
				if (car != car2)
				{
					if (car2->init == false)
						continue;
					else if (car->getFuturePos().intersects(car2->getFuturePos()))
					{
						stop = car->needPassOtherCar(car2);
					}
					if (stop == true)
						break;
				}

			}
			if (stop == false)
			{
				car->move();
			}


			if (intersect_car(car) == true)//вышли за экран
			{
				car->init = false;
			}
		}
		else
		{
			if (setCarRandomPos(car) == false)//меняем позицию
			{
				return false;
			}
			car->init = true;
			for (auto car2 : pull_cars)
			{
				if (car != car2)
				{
					if (car2->init == true)
					{
						if (car->getFuturePos().intersects(car2->getFuturePos()))
						{
							car->init = false;
							break;
						}
					}
				}
			}
			

		}
		
	}
	return true;
}

bool Init_Pull()
{
	pull_cars.resize(initialCarsCount);
	for (size_t n = 0; n < initialCarsCount; n++)
	{
		auto car = spawnRandomCarFromRandomPos();
		if (car == nullptr)
		{
			return false;
		}
		pull_cars[n] = car;
	}
	return true;
}

/*
Все тестовые задания должны быть выполнены Вами самостоятельно и являться результатом исключительно Вашей интеллектуальной деятельности, 
созданы без нарушения прав третьих лиц, незаконных заимствований и плагиата. Направляя результат выполненных тестовых заданий, Вы подтверждаете, 
что понимаете и принимаете тот факт, что ООО "Майтона" могло получить или получать от третьих лиц, либо разработать или разрабатывать самостоятельно материалы, схожие с направленными Вами.
*/