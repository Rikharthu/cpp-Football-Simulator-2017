#include "pch.h"
#include "Utils.h"
#include <cstdlib>
#include <math.h>

#define PI 3.1415926535897932385

using namespace Windows::Foundation;

int random(int low, int high)
{
	return rand() % (high - low + 1) + low;
}

int random(int high) {
	return rand() % high;
}

int distance(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	return sqrt(dx*dx + dy*dy);
}

double direction(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	double dy = y2 - y1;
	if (dx == 0)return dy < 0 ? PI / 2 : 3 * PI / 2;
	else return atan(dy / dx) + (dx > 0 ? PI : 0);

}

// TODO test how it works with cstdlib's rand()
double disperse(double direction, double delta)
{
	int k = rand() % 2 ? -1 : 1;
	double p = rand() % 1001 / 1000;
	return direction + k*p*delta;
}

// WAT IS HAPPENING HERE!?
void angellipse(int SOMETHING, int xc, int yc, int r, double a1, double a2, double ang, double ear) {
	float angr, cosang, sinang, r1, r2, x1, y1, da, a;
	int x, y;
	double Spic_AR = 1;
	if (a1>a2) { a = a1; a1 = a2; a2 = a; }
	da = PI / 200; //0.0698128;
	int np = (a2 - a1) / da + 2;
	Point *poly = new Point[np];
	r1 = r; r2 = r*ear;

	ang = -ang;
	cosang = cos(ang);
	sinang = sin(ang);
	x1 = r1*cos(a1); y1 = r2*sin(a1);
	x = x1*cosang - y1*sinang + xc;
	y = (x1*sinang + y1*cosang)*Spic_AR + yc;
	poly[0].X = x;
	poly[0].Y = y;
	int i = 1;
	for (a = a1 + da; a <= a2; a += da) {
		x1 = r1*cos(a); y1 = r2*sin(a);
		x = x1*cosang - y1*sinang + xc;
		y = (x1*sinang + y1*cosang)*Spic_AR + yc;
		poly[i].X = x;
		poly[i].Y = y;
		++i;
	}

	// TODO

	delete poly;
}
