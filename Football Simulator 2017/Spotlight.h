#pragma once
#include "Drawable.h"

class Spotlight :public Drawable {
private:
	int x, y, r,speed;
	double dir;
	int max_speed = 12;
public:
	Spotlight(int r);
	virtual void draw();
	void move();
};