#include "pch.h"
#include "Girl.h"
#include "Utils.h"
#include "GameManager.h"

Girl::Girl() {
	//aCanvas = FG_Frm->FieldImage->Canvas;
	type = tGirl;
	color = Colors::Fuchsia;
	speed = 5;
}

void Girl::move()
{
	int center_x, center_y;
	gameManager->field->getCentre(center_x, center_y);
	if (speed > 0 && y < 200) speed = 3; else speed = -7;
	y += speed;
	if (y < 5) {
		gameManager->gameState = sRestartGame;
		r = 3;
		speed = 5;
	}
}

void Girl::draw()
{
	if (gameManager->gameState == sPause) {
		r = (r == 3) ? 4 : 3;
	}
	Human::draw();
}
