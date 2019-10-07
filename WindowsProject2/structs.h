#pragma once

//INCLUDE
//STD
#include <stdlib.h>
#include <vector>
#include <string>
//END INCLUDE

enum eDirection {
	TOP,
	LEFT,
	RIGHT,
	BOT
};

//STRUCT
struct sPos 
{
	int x;
	int y;

	sPos() { x = 0; y = 0; }
	sPos(int aX, int aY) { x = aX; y = aY; }
};

struct sSize
{
	int width;
	int height;

	sSize() { width = 0; height = 0; }
	sSize(int aW, int aH) { width = aW; height = aW; }
};


struct sRect
{
	sPos pos;
	sSize size;

	sRect() {};
	sRect(int x, int y, int w, int h) { pos.x = x; pos.y = y; size.width = w; size.height = h; }

	bool intersects(const sRect& other)
	{
		return !
			(
			(other.pos.x + other.size.width < pos.x  ) ||
				(other.pos.y + other.size.height < pos.y ) ||
				(other.pos.x  > pos.x + size.width) ||
				(other.pos.y  > pos.y + size.height)
				);
	}

};
//END STRUCT