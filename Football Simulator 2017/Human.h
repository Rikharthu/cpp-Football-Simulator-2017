#pragma once
#include "Drawable.h"

using namespace Windows::UI;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::Foundation;

enum htype {
	tReferee, tAssReferee,
	tGoalKeeper, tForward,
	tHalfBack, tQuarterBack,
	tFullBack, tGirl
};

class Human : public Drawable
{
protected:
	int x;
	int y;
	int r;
	Color color;
	int speed;
	int energy;
	double dir;
	CanvasRenderTarget^ offscreen;
public:
	Human();
	htype type;
	void setSpeed(int s) { speed = s; }
	void setDir(double d) { dir = d; }
	void setEnergy(int e) { energy = e; };
	int getEnergy() { return energy; };
	Point getPos() { return Point(x, y); }
	double getDir() { return dir; }
	int getSpeed() { return speed; }
	virtual void draw();
	virtual void move() = 0;
	void moveTo(int x, int y);
};