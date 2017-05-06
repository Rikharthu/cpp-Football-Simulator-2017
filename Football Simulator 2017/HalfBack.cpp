#include "pch.h"
#include "HalfBack.h"
#include "GameManager.h"
#include "Utils.h"


HalfBack::HalfBack(int t, int n) :Player(t, n)
{
	speed = 10;
	area = *(gameManager->field->fieldRect);
	type = tHalfBack;
}

void HalfBack::kick()
{
	int ball_x, ball_y, center_x, center_y, direction_x, direction_y;
	double ball_direction, dirdisp = PI / 8;
	int kickSpeed = 35;
	gameManager->ball->getCoord(ball_x, ball_y);
	gameManager->field->getCentre(center_x, center_y);
	direction_y = ball_y;
	if (teamNo == 1) {
		direction_x = gameManager->field->fieldRect->Right;
	}
	else {
		direction_x = gameManager->field->fieldRect->Left;
	}
	if (distance(ball_x, ball_y, direction_x, direction_y) <= 3 * kickSpeed) {
		direction_y = center_y;
		dirdisp = 0;
	}

	ball_direction = direction(ball_x, ball_y, direction_x, direction_y);
	ball_direction = disperse(ball_direction, dirdisp);
	gameManager->ball->setDir(ball_direction);
	gameManager->ball->setSpeed(disperse(kickSpeed, kickSpeed / 2));

	gameManager->sound_queue.push(Kick1);

	gameManager->last_kick_player = No;
	gameManager->last_kick_team = teamNo;
}
