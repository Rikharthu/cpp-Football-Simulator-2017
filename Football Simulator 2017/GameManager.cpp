#include "pch.h"
#include "GameManager.h"
#include <set>
#include "Player.h"
#include "Utils.h"

using namespace std;
using namespace Windows::UI;
using namespace Windows::Foundation;
using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::ApplicationModel::Core;

//*** Configure layers used during initialization here ****
#define LAYER_NUMBER_PLAYERS 7;
#define LAYER_NUMBER_BALL 6;
#define LAYER_NUMBER_FIELD 0;
#define LAYER_NUMBER_FIELD_NET 100;
#define LAYER_NUMBER_REFEREES 8;
// most important
#define LAYER_NUMBER_GIRLS 100500;
// TODO

GameManager::GameManager(CanvasCommandList ^cl)
{
	this->field_cl = cl;
}

void GameManager::init()
{
	this->field = new Field();
	FieldNet * net = new FieldNet();
	net->layer = LAYER_NUMBER_FIELD_NET;
	drawables.push_back(net);
	this->render_target = ref new CanvasRenderTarget(this->canvas, this->canvas->Size);
	this->ball = new Ball();
	ball->layer = 100;
	drawables.push_back(ball);

	// generate players
	for (int i = 0; i < 7; i++) {
		Player * new_player = new Player(1, i + 1);
		new_player->layer = LAYER_NUMBER_PLAYERS;
		team1.push_back(new_player);
		//TODO debug
		new_player->moveTo(random(601), random(601));
		drawables.push_back(new_player);

		new_player = new Player(2, i + 1);
		new_player->layer = LAYER_NUMBER_PLAYERS;
		team2.push_back(new_player);
		//TODO debug
		new_player->moveTo(random(601), random(601));
		drawables.push_back(new_player);
		int a = 4;
	}
}

void GameManager::render()
{
	CanvasDrawingSession ^ clds = gameManager->render_target->CreateDrawingSession();
	clds->Clear(Colors::Transparent);
	delete clds;
	//TODO add possible layer values to layers (will be used for rendering order)
	//TODO move recalculations to another method like "recalculateLayersAndDrawables"

	set<int> layers;
	for (Drawable* drawable : drawables) {
		layers.insert(drawable->layer);
	}
	// set is automatically ordered
	for (int layer : layers) {
		// render all Drawables for given layer
		for (Drawable *drawable : drawables) {
			if (drawable->layer == layer) {
				//drawable.draw();
				drawable->draw();
				int a = 4;
			}
		}
	}

}