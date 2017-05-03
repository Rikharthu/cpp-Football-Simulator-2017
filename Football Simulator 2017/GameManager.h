#pragma once
#include "Field.h"

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;

class GameManager {
public:
	CanvasAnimatedControl ^ canvas;
	///<summary>
	/// Command list where we will draw our field
	///</summary>
	CanvasCommandList ^ field_cl;
	Field * field;
	///<summary>
	/// A bitmap we will draw dynamic content on to
	///</summary>
	CanvasRenderTarget ^ render_target;

	GameManager(CanvasCommandList^);

	void init();
};

extern GameManager * gameManager;