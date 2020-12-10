#ifndef __MEDIATOR_H__
#define __MEDIATOR_H__
#include "Game.h"
#include "Point.h"
#include "abstractFactory.h"
#include <sstream>
#include <vector>

class Mediator
{
public:
	double rate;
	Mediator()
	{
		rate = 1.0;
	}
	void checkrate(Enemy* enemy, Point* points)
	{
		if (points->score >= 100)
			this->increaseSpeed(enemy);
	}
	void increaseSpeed(Enemy* enemy)
	{
		enemy->speed += this->rate;
	}
};

#endif