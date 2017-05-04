#pragma once
#include "Drawable.h"

class Lights :public Drawable {
private:
	int x;
	int y;
	double dir;
	double dirStart, dirEnd;
	double dirSpeed;
	double focus;
	int towerHeight;
	double tilt;
	double tiltStart, tiltEnd;
	double tiltSpeed;

public:
	bool on;
	Lights(int xp, int yp, int towerH,
		double foc,
		double dir1, double dir2,
		double tilt1, double tilt2);
	virtual void draw();
	void move();
	void moveTo(int xTo, int yTo) { x = xTo; y = yTo; }
};