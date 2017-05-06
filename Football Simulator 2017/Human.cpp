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
	gameManager->render_target_session->FillCircle(x, y, r, color);
}

void Human::moveTo(int xTo, int yTo)
{
	x = xTo; y = yTo;
}
