#pragma once
#include "Human.h"

using namespace Windows::Foundation::Numerics;

class Player :public Human
{
protected:
	int teamNo;
	int No;
	Rect area;
public:
	Player(int t, int n);
	virtual void move();
	virtual void draw();
	virtual void kick();
	void avoidCollision();
	bool inGame;
	void moveToBench();
	// Get Point representing the closest partner's coordinates
	// If returned point's X coordinate is -1 (<0), then no eligible partner was found
	Point& partner();
};