#include "pch.h"
#include "Human.h"
#include "GameManager.h"

Human::Human()
{
	r = 6;
	speed = 0;
	energy = 0;
	dir = 0;
	color = Colors::Cyan;
}

void Human::draw()
{
	CanvasDrawingSession ^ clds = gameManager->render_target->CreateDrawingSession();
	clds->FillCircle(x, y, r, color);
	delete clds;
}

void Human::moveTo(int xTo, int yTo)
{
	x = xTo; y = yTo;
}
