#pragma once
#include "Field.h"
#include "Ball.h"
#include <list>
#include "Drawable.h"
#include "Player.h"
#include "Spotlight.h"
#include "Sound.h"
#include "Referee.h"
#include "AssReferee.h"
#include "Girl.h"
#include <queue>
#include "Lights.h"

using namespace std;

using namespace Microsoft::Graphics::Canvas::UI::Xaml;
using namespace Microsoft::Graphics::Canvas;
using namespace Windows::UI::Xaml::Controls;

enum state { sStop, sRunning, sPause, sGoal, sRestartGame, sFirstKick };

class GameManager {
public:
	GameManager(CanvasCommandList^);
	~GameManager();

	CanvasAnimatedControl ^ canvas;
	// Command list where we will draw our field
	CanvasCommandList ^ field_cl;

	// Game objects
	Field * field;
	Ball * ball;
	// A bitmap we will draw dynamic content on to
	CanvasRenderTarget ^ render_target;
	// Contains all the object that are going to be drawn for batch-rendering
	list<Drawable*> drawables;
	vector<Player*> team1;
	vector<Player*> team2;
	vector<Girl*> girls;
	Referee * ref1;
	AssReferee * assRef1;
	AssReferee * assRef2;
	Spotlight * spotlight;
	Lights *lights[2];
	char last_kick_team = -1;
	char last_kick_player = -1;

	// params for ui
	//String^ message;
	int team1_energy = 0;
	int team2_energy = 0;
	int time = 0;
	void init();
	int team1_score = 0;
	int team2_score = 0;
	Sound sound;
	bool isLoopSound = false;
	// sounds sequences that should be played
	queue<Sound> sound_queue;

	// Configurations
	bool isGirlsAllowed = false;
	state gameState = sStop;

	void render();

	void moveAll();

	void calculateEnergy();

	void startGame();

	void position0();
	void position1();
	void position2();

	// Calls all the move methods, checks the game state and etc.
	void tick();
};

extern GameManager * gameManager;