#include "pch.h"
#include "FieldNet.h"
#include "GameManager.h"

void FieldNet::draw()
{
	// lazy init for brush
	//if (net_brush == nullptr || image == nullptr) {
		// configure net brush pattern
		//TODO implement
		image = ref new CanvasRenderTarget(gameManager->canvas, gameManager->canvas->Size);
		CanvasDrawingSession ^ net_clds = image->CreateDrawingSession();
		// our pattern will consist of rounded rectangles
		net_clds->DrawRoundedRectangle(0, 0, 8, 8, 3, 3, Colors::MintCream, 1);
		delete net_clds;

		// configure net brush to repeat this pattern
		net_brush = ref new CanvasImageBrush(gameManager->canvas, image);
		net_brush->SourceRectangle = Rect(0, 0, 8, 8);
		net_brush->ExtendX = CanvasEdgeBehavior::Mirror;
		net_brush->ExtendY = CanvasEdgeBehavior::Mirror;

		CanvasDrawingSession ^ session = gameManager->render_target->CreateDrawingSession();
		Field field = *gameManager->field;
		// left
		session->DrawRectangle(Rect(0, field.y_c - field.goalWidth / 2, field.borderWidth, field.goalWidth), Colors::White);
		session->FillRectangle(Rect(0, field.y_c - field.goalWidth / 2, field.borderWidth, field.goalWidth), net_brush);

		// right
		// fieldRect->Right == w+borderWidth
		session->DrawRectangle(Rect(field.fieldRect->Right, field.y_c - field.goalWidth / 2, field.borderWidth, field.goalWidth), Colors::White);
		session->FillRectangle(Rect(field.fieldRect->Right, field.y_c - field.goalWidth / 2, field.borderWidth, field.goalWidth), net_brush);
		delete session;
	//}

	// we have it pre-drawn in image
	/*session = gameManager->render_target->CreateDrawingSession();
	session->DrawImage(image);
	delete session;*/
}