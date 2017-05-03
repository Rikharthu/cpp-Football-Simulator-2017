#include "pch.h"
#include "FullBack.h"
#include "GameManager.h"
#include "Utils.h"

FullBack::FullBack(int t, int n) :Player(t, n)
{
	speed = 5;
	int center_x, center_y;
	gameManager->field->getCentre(center_x, center_y);
	// Where FullBack is allowed to operate
	if (teamNo == 1) {
		area = Rect(gameManager->field->fieldRect->Left,
			gameManager->field->fieldRect->Top,
			(gameManager->field->fieldRect->Width) / 2,
			gameManager->field->fieldRect->Height);
	}
	else {
		area = Rect(center_x,
			gameManager->field->fieldRect->Top,
			(gameManager->field->fieldRect->Width) / 2,
			gameManager->field->fieldRect->Height);
	}
	type = tFullBack;
}

void FullBack::move()
{
	if (!inGame) {
		moveToBench(); return;
	}
	int close = 2 * r;
	int xb, yb, xc, yc, xd, yd;
	gameManager->ball->getCoord(xb, yb);
	gameManager->field->getCentre(xc, yc);

	energy = energy > 0 ? --energy : 0;
	speed = 3;// + rand(energy / 1000);

	xd = xb; yd = yb;
	if (teamNo == 1 && xb > xc) { xd = disperse(xc / 2, xc / 4); yd = random(2 * yc); }
	if (teamNo == 2 && xb < xc) { xd = disperse(xc + xc / 2, xc / 4);  yd = random(2 * yc); }

	dir = direction(x, y, xd, yd);
	//dir = disperse(dir, PI/6);

	x += speed*cos(dir);
	y -= speed*sin(dir);
	if (x < area.Left) x = area.Left + 2 * r;
	if (x > area.Right) x = area.Right - 2 * r;

	avoidCollision();

	if (distance(x, y, xb, yb) < close) kick();
}

void FullBack::kick()
{
	int ball_x, ball_y, center_x, center_y;
	gameManager->ball->getCoord(ball_x, ball_y);
	gameManager->field->getCentre(center_x, center_y);

	if (teamNo == 1) {
		center_x = gameManager->field->fieldRect->Right;
	}
	else {
		center_x = gameManager->field->fieldRect->Left;
	}

	double ball_direction = direction(ball_x, ball_y, center_x, center_y);
	ball_direction = disperse(ball_direction, PI / 8);
	gameManager->ball->setDir(ball_direction);
	gameManager->ball->setSpeed(30);
	//TODO replace with Sound enum value
	sound = 1;
}
