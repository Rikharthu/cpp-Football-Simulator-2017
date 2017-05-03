#include "pch.h"
#include "AssReferee.h"
#include "GameManager.h"
#include "Utils.h"

AssReferee::AssReferee()
{
	type = tAssReferee;
	color = Colors::Lime;
	speed = 2;
}

void AssReferee::move()
{
	int ball_x, ball_y;
	gameManager->ball->getCoord(ball_x, ball_y);
	//TODO debug here to adjust
	int delta = rand()&abs(ball_x - x);
	delta = delta > 5 ? 5 : delta;
	if (x < ball_x) x += speed + delta;
	if (x > ball_x)x -= speed + delta;
}
