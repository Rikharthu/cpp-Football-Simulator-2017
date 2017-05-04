#include "pch.h"
#include "GoalKeeper.h"
#include "GameManager.h"
#include "Utils.h"

GoalKeeper::GoalKeeper(int t, int n) :Player(t, n)
{
	speed = 1;
	color = t == 1 ? Colors::LightBlue : Colors::Maroon;
	int center_x, center_y;
	gameManager->field->getCentre(center_x, center_y);
	int goal_width, goal_height;
	gameManager->field->getGoalArea(goal_width, goal_height);
	if (teamNo == 1) {
		area = Rect(gameManager->field->fieldRect->Left,
			center_y - goal_height / 2,
			goal_width,
			goal_height);
	}
	else {
		area = Rect(gameManager->field->fieldRect->Right - goal_width,
			center_y - goal_height / 2,
			goal_width,
			goal_height);
	}
	type = tGoalKeeper;
}

void GoalKeeper::move()
{
	int close = 2 * r;
	int ball_x, ball_y;
	gameManager->ball->getCoord(ball_x, ball_y);

	speed = 5;// + random(5);          //

	dir = direction(x, y, ball_x, ball_y);
	dir = disperse(dir, PI / 8);

	x += speed*cos(dir);
	y -= speed*sin(dir);

	if (x < area.Left) x = area.Left + 2 * r;
	if (x > area.Right) x = area.Right - 2 * r;
	if (y < area.Top) y = area.Top + 2 * r;
	if (y > area.Bottom) y = area.Bottom - 2 * r;

	avoidCollision();

	if (distance(x, y, ball_x, ball_y) < close) kick();
}

void GoalKeeper::kick()
{
	if (gameManager->ball->immune_counter<= 0) {
		int bal_x, ball_y, center_x, center_y;
		gameManager->ball->getCoord(bal_x, ball_y);
		gameManager->field->getCentre(center_x, center_y);

		if (teamNo == 1) {
			center_x = gameManager->field->fieldRect->Right;
		}
		else {
			center_x = gameManager->field->fieldRect->Left;
		}
		double ball_direction = direction(bal_x, ball_y, center_x, center_y);
		ball_direction = disperse(ball_direction, PI / 4);
		gameManager->ball->setDir(ball_direction);
		gameManager->ball->setSpeed(40);
		gameManager->ball->immune_counter = 20;

		//TODO some lagg happens with this sound, even though during debugging it is confirmed to execute only once
		gameManager->sound_queue.push(Kick3);
	}
}
