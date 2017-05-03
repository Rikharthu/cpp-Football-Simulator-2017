#pragma once
#include "Field.h"
#include "Ball.h"
#include <list>
#include "Drawable.h"
#include "Player.h"

using namespace std;

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI::Xaml::Controls;

enum state { sStop, sRunning, sPause, sGoal, sRestartGame, sFirstKick };

class GameManager {
public:
	CanvasAnimatedControl ^ canvas;
	///<summary>
	/// Command list where we will draw our field
	///</summary>
	CanvasCommandList ^ field_cl;
	Field * field;
	Ball * ball;
	///<summary>
	/// A bitmap we will draw dynamic content on to
	///</summary>
	CanvasRenderTarget ^ render_target;
	//TODO add all Drawables to this list
	///<summary>
	/// Contains all the object that are going to be drawn for batch-rendering
	///</symmary>
	std::list<Drawable*> drawables;
	vector<Player*> team1;
	vector<Player*> team2;
	state gameState;

	GameManager(CanvasCommandList^);

	void init();

	void render();
};

extern GameManager * gameManager;