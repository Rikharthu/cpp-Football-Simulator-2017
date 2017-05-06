#pragma once
#include "FieldNet.h"

using namespace Windows::Foundation;
using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Brushes;

class Field
{
private:
	int h;
	int w;
	int x_c;
	int y_c;
	int markupWidth;
	int borderWidth;
	int goalWidth;
	int goalAreaW;
	int goalAreaH;
	CanvasImageBrush ^ net_brush;
	CanvasCommandList ^ goal_net_cl;

public:
	Rect *fieldRect;
	Field();
	void getCentre(int& x, int& y) { x = x_c; y = y_c; }
	void getGoalArea(int& w, int& h) { w = goalAreaW; h = goalAreaH; }
	int getBorderW() { return borderWidth; }
	int getH() { return h; }
	int getW() { return w; }
	void draw(CanvasDrawingSession^ clds);
	void draw();
	void drawLines();
	bool isInside(int x, int y);
	bool isOutSide(int x, int y);
	bool isOutLeft(int x, int y);
	bool isOutRight(int x, int y);
	bool onLeft(int x, int y);
	bool onRight(int x, int y);
	bool isGoalLeft(int x, int y);
	bool isGoalRight(int x, int y);
	bool insideLeftGoalArea(int x, int y);
	bool insideRightGoalArea(int x, int y);
	friend void FieldNet::draw();
};
