#pragma once
#include <string>
using namespace std;
using namespace Microsoft::Graphics::Canvas;
#define PI 3.1415926535897932385

// generates an integer in range [low; high]
int random(int low, int high);
// generates an integer in range [0; high)
int random(int high);
// calculates distance between 2 points
int distance(int x1, int y1, int x2, int y2);
double direction(int x1, int y1, int x2, int y2);
double disperse(double direction, double delta);
void angellipse(CanvasDrawingSession^ clds, int xc, int yc, int r, double a1, double a2, double ang, double ear);
Platform::String^ toPlatformString(string str);