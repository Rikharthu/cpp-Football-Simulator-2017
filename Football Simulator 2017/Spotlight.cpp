#include "pch.h"
#include "Spotlight.h"
#include "GameManager.h"
#include "Utils.h"

using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI;

Spotlight::Spotlight(int r)
{
	x = 10;
	y = 10;
	this->r = r;
	speed = 10;
}

void Spotlight::draw() {
	//TODO lazy init for brush
	CanvasSolidColorBrush^ brush = ref new CanvasSolidColorBrush(gameManager->canvas, Colors::LightGoldenrodYellow);
	brush->Opacity = 0.2f;
	gameManager->render_target_session->FillCircle(x, y, r, brush);
}

void Spotlight::move()
{
	int ball_x, ball_y;
	gameManager->ball->getCoord(ball_x, ball_y);

	dir = direction(x, y, ball_x, ball_y);
	dir = disperse(dir, PI / 12);

	x += speed*cos(dir);
	y -= speed*sin(dir);

	int distance_to_ball = distance(x, y, ball_x, ball_y);
	int close = r;
	if (distance_to_ball < close) {
		float k = (float)distance_to_ball / close;
		speed =(max_speed-1)* k+1;
	}
	else {
		speed = max_speed;
	}
}
