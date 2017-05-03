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
	CanvasDrawingSession ^ session = gameManager->render_target->CreateDrawingSession();
	session->FillCircle(x, y, r, Colors::White);
	session->DrawCircle(x, y, r, Colors::Black);
	delete session;
}

void Ball::move()
{
}

bool Ball::isCollide(int x, int y, int r)
{
	return distance(this->x, this->y, x, y) <= this->r + r;
}
