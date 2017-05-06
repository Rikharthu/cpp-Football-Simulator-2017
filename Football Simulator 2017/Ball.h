#pragma once
#include "Drawable.h"

class Ball :public Drawable
{
private:
	int x;
	int y;
	int r;
	int speed;
	int slowdown;
	double dir;
public:
	Ball();
	void setSpeed(int s) { speed = s; }
	int getSpeed() { return speed; }
	void setDir(double d) { dir = d; }
	double getDir() { return dir; }
	virtual void draw();
	void move();
	void moveTo(int xTo, int yTo) { x = xTo; y = yTo; }
	void getCoord(int& xb, int& yb) { xb = x; yb = y; }
	bool isCollide(int x, int y, int r);

	int immune_counter = 0;
};
