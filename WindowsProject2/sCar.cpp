#include "sCar.h"
	sCar::sCar() { speed = 0; }

	void sCar::move()
	{
		switch (dir)
		{
		case eDirection::TOP:
		{
			rect.pos.y -= speed;
			break;
		}
		case eDirection::BOT:
		{
			rect.pos.y += speed;
			break;
		}
		case eDirection::RIGHT:
		{
			rect.pos.x += speed;
			break;
		}
		case eDirection::LEFT:
		{
			rect.pos.x -= speed;
			break;
		}
		}
	}

	sRect sCar::getFuturePos()
	{
		switch (dir)
		{
		case eDirection::TOP:
			return sRect(rect.pos.x, rect.pos.y - speed, rect.size.width, rect.size.height);
		case eDirection::BOT:
			return sRect(rect.pos.x, rect.pos.y + speed, rect.size.width, rect.size.height);
		case eDirection::RIGHT:
			return sRect(rect.pos.x + speed , rect.pos.y, rect.size.width, rect.size.height);
		case eDirection::LEFT:
			return sRect(rect.pos.x - speed , rect.pos.y, rect.size.width, rect.size.height);
		}
	}

	bool sCar::needPassOtherCar(sCar* otherCar)
	{
		bool result = false;
		auto otherdir = otherCar->dir;//����������� ������
		const int size_car_smeh = 20;//���������� ��� ������������� ��������
		switch (dir)
		{
		case eDirection::TOP://TOP
		{
			switch (otherdir)
			{
			case eDirection::TOP:
			{
				if (otherCar->rect.pos.y < rect.pos.y)
				{
					result = true;
				}
				break;
			}
			case eDirection::LEFT://��� ����������� TOP, � ������ ������� � ��� ������ � ������������ LEFT
			{
				if (otherCar->rect.pos.x + otherCar->rect.size.width > rect.pos.x)//���� ���� ������ ����� ���������� �����
				{
					if (otherCar->rect.pos.y + otherCar->rect.size.height < rect.pos.y)
					{
						result = true;
					}
				}
				break;
			}
			case eDirection::RIGHT:
			{
				if (otherCar->rect.pos.x + otherCar->rect.size.width + size_car_smeh > rect.pos.x)
				{
					if (otherCar->rect.pos.y + otherCar->rect.size.height < rect.pos.y)
					{
						result = true;
					}
				}

				break;
			}
			default:
			{
				break;
			}
			}
			break;//END TOP
		}
		case eDirection::BOT://BOT
		{
			switch (otherdir)
			{
			case eDirection::BOT:
			{
				if (otherCar->rect.pos.y > rect.pos.y)
				{
					result = true;
				}
				break;
			}
			case eDirection::LEFT:
			{
				if (otherCar->rect.pos.x  < rect.pos.x + rect.size.width)//���� ���� ������ � ������������ LEFT - ����������
				{
					if (otherCar->rect.pos.y > rect.pos.y + rect.size.height)
					{
						result = true;
					}
				}
				break;
			}
			case eDirection::RIGHT://��� ����������� BOT, � ������ ������� � ��� ������ � ������������ RIGHT
			{
				if (otherCar->rect.pos.x + otherCar->rect.size.width + size_car_smeh> rect.pos.x)
				{
					if (otherCar->rect.pos.y > rect.pos.y + rect.size.height)
					{
						result = true;
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;//END BOT
		}
		case eDirection::RIGHT://RIGHT - � ���� �� ������� ����������� ���������� x
		{
			switch (otherdir)
			{
			case eDirection::RIGHT:
			{
				if (otherCar->rect.pos.x > rect.pos.x)
				{
					result = true;
				}
				break;
			}
			case eDirection::TOP:
			{
				if (otherCar->rect.pos.x > rect.pos.x + rect.size.width )//��� ����������� RIGTH, � ������ ������� � ��� ������ � ������������ TOP
				{
					if (otherCar->rect.pos.y < rect.pos.y + rect.size.height)
					{
						result = true;
					}
				}
				break;
			}
			case eDirection::BOT:
			{
				if (otherCar->rect.pos.y + otherCar->rect.size.height > rect.pos.y)
				{
					result = true;
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;//END RIGHT
		}
		case eDirection::LEFT://LEFT
		{
			switch (otherdir)
			{
			case eDirection::LEFT:
			{
				if (otherCar->rect.pos.x < rect.pos.x)
				{
					result = true;
				}
				break;
			}
			case eDirection::TOP:
			{
				if (otherCar->rect.pos.y < rect.pos.y + rect.size.height)
				{
					result = true;
				}
				break;
			}
			case eDirection::BOT://��� ����������� LEFT, � ������ ������� � ��� ������ � ������������ BOT
			{
				if (otherCar->rect.pos.x + otherCar->rect.size.width < rect.pos.x)
				{
					if (otherCar->rect.pos.y + otherCar->rect.size.height + size_car_smeh > rect.pos.y)
					{
						result = true;
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
			break;//END LEFT
		}
		}//END SWITCH


		return result;
	}//END FUNC
	



