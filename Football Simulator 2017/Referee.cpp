#include "pch.h"
#include "Referee.h"
#include "GameManager.h"
#include "Utils.h"

Referee::Referee()
{
	// aCanvas = FG_Frm->FieldImage->Canvas;
	type = tReferee;
	color = Colors::Yellow;
	speed = 0;
}

void Referee::move()
{
	int ball_x, ball_y;
	gameManager->ball->getCoord(ball_x, ball_y);
	dir = direction(x, y, ball_x, ball_y);
	dir = disperse(dir, PI / 8);
	if (distance(x, y, ball_x, ball_y) < 50) {
		// to close to the ball => move away
		dir = -dir;
	}
	speed = 3 + rand() % 3;
	x += speed*cos(dir);
	y -= speed*sin(dir);
}
