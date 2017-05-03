#pragma once
#include "Drawable.h"

using namespace Windows::Foundation;
using namespace Microsoft::Graphics::Canvas;
using namespace Microsoft::Graphics::Canvas::Brushes;

class FieldNet :public Drawable {
private:
	CanvasImageBrush ^ net_brush;
	CanvasRenderTarget ^ image;
public:
	virtual void draw();
};