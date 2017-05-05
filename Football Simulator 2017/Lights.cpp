#include "pch.h"
#include "Lights.h"
#include "Utils.h"
#include "GameManager.h"

using namespace Windows::Foundation;
using namespace Microsoft::Graphics::Canvas::Geometry;

bool isOldImplementation = true;

Lights::Lights(int xp, int yp, int towerH, double foc, double dir1, double dir2, double tilt1, double tilt2)
{
	x = xp;
	y = yp;
	dir = dir1;
	dirStart = dir1;
	dirEnd = dir2;
	dirSpeed = PI / 64;
	focus = foc;
	towerHeight = towerH;
	tilt = tilt1;
	tiltStart = tilt1;
	tiltEnd = tilt2;
	tiltSpeed = PI / 48;
	on = false;
}

void Lights::draw()
{
	if (on) {
		int dist = towerHeight*tan(tilt);
		int xspot = x + dist*cos(dir);
		int yspot = y - dist*sin(dir);

		if (!isOldImplementation) {
			poly = ref new Platform::Array<float2>(3);

			poly[0].x = x;
			poly[0].y = y;

			int d1 = dist / sin(tilt);

			int spotLength = towerHeight*tan(tilt - focus / 2) - towerHeight*tan(tilt + focus / 2);
			int spotWidth = 2 * d1*tan(focus / 2);

			int x1 = xspot - spotWidth / 2 * sin(dir);
			int y1 = yspot - spotWidth / 2 * cos(dir);
			int x2 = xspot + spotWidth / 2 * sin(dir);
			int y2 = yspot + spotWidth / 2 * cos(dir);

			poly[1].x = x1;
			poly[1].y = y1;
			poly[2].x = x2;
			poly[2].y = y2;

			CanvasSolidColorBrush^ brush = ref new CanvasSolidColorBrush(gameManager->canvas, Colors::YellowGreen);
			brush->Opacity = 0.7f;
			CanvasDrawingSession^  clds = gameManager->render_target->CreateDrawingSession();
			clds->FillGeometry(CanvasGeometry::CreatePolygon(clds, poly), brush);
			angellipse(clds, xspot, yspot, spotLength / 2, 0, 2 * PI, dir, spotWidth*1.0 / spotLength);
			delete clds;
		}
		else {
			// Old Implementation
			/*Point poly[3];
			poly[0].X = x;
			poly[0].Y = y;*/

			int xspot = x + dist*cos(dir);
			int yspot = y - dist*sin(dir);

			CanvasSolidColorBrush^ brush = ref new CanvasSolidColorBrush(gameManager->canvas, Colors::YellowGreen);
			brush->Opacity = 0.7f;
			CanvasDrawingSession ^ session = gameManager->render_target->CreateDrawingSession();
			session->FillCircle(xspot, yspot, 100, brush);

			// no need, but still
			delete session;
			delete brush;
		}
	}
}

void Lights::move()
{
	if (dir >= dirStart && dirSpeed > 0) dirSpeed = -PI / 64;
	if (dir <= dirEnd && dirSpeed < 0) dirSpeed = PI / 64;
	dir += dirSpeed;
	if (tilt <= tiltStart && tiltSpeed < 0) tiltSpeed = PI / 48;
	if (tilt >= tiltEnd && tiltSpeed > 0) tiltSpeed = -PI / 48;
	tilt += tiltSpeed;
}
