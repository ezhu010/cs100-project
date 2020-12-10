
#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
public:
	int score;
	Point()
	{
		score = 0;
	}

	void incrementEasy()
	{
		score += 1;
	}

	void incrementHard()
	{
		score += 7;
	}
};

#endif
