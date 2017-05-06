#include "pch.h"
#include "Ball.h"
#include "GameManager.h"
#include "Utils.h"

using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI;

extern GameManager * gameManager;

Ball::Ball()
{
	r = 8;
	speed = 0;
	slowdown = 3;
	dir = 0;
}

void Ball::draw()
{
	gameManager->render_target_session->FillCircle(x, y, r, Colors::White);
	gameManager->render_target_session->DrawCircle(x, y, r, Colors::Black);
}

void Ball::move()
{
	if (immune_counter > 0) {
		immune_counter--;
	}

	if (speed == 0) return;
	bool is_in = gameManager->field->isInside(x, y);
	x += speed*cos(dir);
	y -= speed*sin(dir);
	bool willbe_in = gameManager->field->isInside(x, y);

	speed = speed<slowdown ? 0 : speed - slowdown;

	int xc, yc, wg, hg;
	gameManager->field->getCentre(xc, yc);
	gameManager->field->getGoalArea(wg, hg);

	if (gameManager->field->isGoalLeft(x, y)) { x = gameManager->field->fieldRect->Left - 4 * r; return; }
	if (gameManager->field->isGoalRight(x, y)) { x = gameManager->field->fieldRect->Right + 4 * r; return; }
	if (is_in && !willbe_in) {
		if (gameManager->field->isOutSide(x, y)) dir = 2 * PI - dir;
		if (gameManager->field->isOutRight(x, y)) {
			moveTo(gameManager->field->fieldRect->Right - wg, yc);
			speed = 0;
		}
		if (gameManager->field->isOutLeft(x, y)) {
			moveTo(gameManager->field->fieldRect->Left + wg, yc);
			speed = 0;
		}
	}
}

bool Ball::isCollide(int x, int y, int r)
{
	return distance(this->x, this->y, x, y) <= this->r + r;
}
