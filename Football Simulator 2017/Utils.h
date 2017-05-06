#pragma once
#include <string>
using namespace std;
using namespace Microsoft::Graphics::Canvas;
#define PI 3.1415926535897932385

///<summary>
/// generates an integer in range [low; high]
///</summary>
int random(int low, int high);

///<summary>
/// generates an integer in range [0; high)
///</summary>
int random(int high);

///<summary>
/// calculates distance between 2 points
///</summary>
int distance(int x1, int y1, int x2, int y2);

///<summary>
/// calculates an angle from x1, y1 to x2, y2
///</summary>
double direction(int x1, int y1, int x2, int y2);

///<summary>
/// does something cool
///</summary>
double disperse(double direction, double delta);

void angellipse(CanvasDrawingSession^ clds, int xc, int yc, int r, double a1, double a2, double ang, double ear);

Platform::String^ toPlatformString(string str);