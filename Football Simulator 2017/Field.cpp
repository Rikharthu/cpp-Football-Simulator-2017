#include "pch.h"
#include "Field.h"
#include "GameManager.h"

using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;

#ifndef FIELD_MARKUP_WIDTH
#define FIELD_MARKUP_WIDTH 3
#endif // !FIELD_MARKUP_WIDTH
#ifndef FIELD_CENTER_RATIO
#define FIELD_CENTER_RATIO 0.7
#endif // !FIELD_CENTER_RATIO

Field::Field()
{
	borderWidth = gameManager->canvas->ActualHeight / 20;
	markupWidth = borderWidth / 4;
	fieldRect = new Rect(borderWidth, borderWidth, gameManager->canvas->ActualWidth - 2 * borderWidth, gameManager->canvas->ActualHeight - 2 * borderWidth);
	//fieldRect = new Rect(4, 4, 400-4, 300-4);

	h = fieldRect->Height;
	w = fieldRect->Width;

	goalWidth = h / 8;
	goalAreaH = goalWidth * 2;
	goalAreaW = goalWidth*0.75;

	x_c = w / 2 + borderWidth;
	y_c = h / 2 + borderWidth;
}

void Field::draw()
{
	CanvasDrawingSession^ session = gameManager->field_cl->CreateDrawingSession();
	// black foundation (draw with borders)
	session->FillRectangle(0, 0, fieldRect->Width + 2 * borderWidth, fieldRect->Height + 2 * borderWidth, Colors::Black);
	// green grass (without borders)
	session->FillRectangle(fieldRect->X, fieldRect->Y, w, h, Colors::Green);
	// white markup
	session->DrawCircle(x_c, y_c, h / 2 * FIELD_CENTER_RATIO, Colors::White, markupWidth);
	session->FillCircle(x_c, y_c, 2 * markupWidth, Colors::White);
	session->DrawLine(x_c, borderWidth, x_c, h + borderWidth, Colors::White, markupWidth);

	// goalkeeper's borders
	session->DrawRectangle(fieldRect->Left, y_c - goalAreaH / 2, goalAreaW, goalAreaH, Colors::White);
	session->DrawRectangle(fieldRect->Right - goalAreaW, y_c - goalAreaH / 2, goalAreaW, goalAreaH, Colors::White);

	delete session;
}

/// <summary>
/// draws football net
/// </summary>
void Field::drawLines()
{
	// lazy init for brush
	if (net_brush == nullptr) {
		// configure net brush pattern
		goal_net_cl = ref new CanvasCommandList(gameManager->canvas);
		CanvasDrawingSession ^ net_clds = goal_net_cl->CreateDrawingSession();
		// our pattern will consist of rounded rectangles
		net_clds->DrawRoundedRectangle(0, 0, 8, 8, 3, 3, Colors::MintCream, 1);
		delete net_clds;

		// configure net brush to repeat this pattern
		net_brush = ref new CanvasImageBrush(gameManager->canvas, goal_net_cl);
		net_brush->SourceRectangle = Rect(0, 0, 8, 8);
		net_brush->ExtendX = CanvasEdgeBehavior::Mirror;
		net_brush->ExtendY = CanvasEdgeBehavior::Mirror;
	}

	CanvasDrawingSession^ session = gameManager->field_cl->CreateDrawingSession();

	// left
	session->DrawRectangle(Rect(0, y_c - goalWidth / 2, borderWidth, goalWidth), Colors::White);
	session->FillRectangle(Rect(0, y_c - goalWidth / 2, borderWidth, goalWidth), net_brush);

	// right
	// fieldRect->Right == w+borderWidth
	session->DrawRectangle(Rect(fieldRect->Right, y_c - goalWidth / 2, borderWidth, goalWidth), Colors::White);
	session->FillRectangle(Rect(fieldRect->Right, y_c - goalWidth / 2, borderWidth, goalWidth), net_brush);

	delete session;
}

bool Field::isInside(int x, int y)
{
	return x >= fieldRect->Left && x <= fieldRect->Right && y >= fieldRect->Top && y <= fieldRect->Bottom;
}

// TODO refactor and use isInside ?
bool Field::isOutSide(int x, int y)
{
	return y<fieldRect->Top || y>fieldRect->Bottom;;
}

bool Field::isOutLeft(int x, int y)
{
	return x < fieldRect->Left;
}

bool Field::isOutRight(int x, int y)
{
	return x > fieldRect->Right;
}

bool Field::onLeft(int x, int y)
{
	return false;
}

bool Field::onRight(int x, int y)
{
	return false;
}

// TODO refactor duplicate code
bool Field::isGoalLeft(int x, int y)
{
	return isOutLeft(x, y) && ((y > (y_c - goalWidth / 2)) && (y < (y_c + goalWidth / 2)));
}

bool Field::isGoalRight(int x, int y)
{
	return isOutRight(x, y) && ((y >(y_c - goalWidth / 2)) && (y < (y_c + goalWidth / 2)));
}

bool Field::insideLeftGoalArea(int x, int y)
{
	return false;
}

bool Field::insideRightGoalArea(int x, int y)
{
	return false;
}
