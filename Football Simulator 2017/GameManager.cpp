#include "pch.h"
#include "GameManager.h"
#include <set>
#include "Player.h"
#include "Utils.h"
#include <algorithm>
#include "Forward.h"
#include "HalfBack.h"
#include "FullBack.h"
#include "GoalKeeper.h"

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
#define LAYER_NUMBER_FIELD_NET 50;
#define LAYER_NUMBER_REFEREES 8;
#define LAYER_NUMBER_SPOTLIGHT 100;
#define LAYER_NUMBER_LIGHTS 5;
// most important
#define LAYER_NUMBER_GIRLS 100500;
#define LAYER_NUMBER_SPOTLIGHT 100;
#define PARAM_SPOTLIGHT_RADIUS 100;
// TODO

GameManager::GameManager(CanvasCommandList ^cl)
{
	this->field_cl = cl;
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
	this->field = new Field();
	FieldNet * net = new FieldNet();
	net->layer = LAYER_NUMBER_FIELD_NET;
	drawables.push_back(net);

	// prepare sessions and drawing targets
	this->render_target = ref new CanvasRenderTarget(this->canvas, this->canvas->Size);

	this->ball = new Ball();
	ball->layer = LAYER_NUMBER_BALL;
	drawables.push_back(ball);

	this->spotlight = new Spotlight(100);
	this->spotlight->layer = LAYER_NUMBER_SPOTLIGHT;
	drawables.push_back(spotlight);

	// generate players
	Player * new_player;
	int number = 0;
	// 3 forwards, 1 halfback, 2 fullbacks and 1 goalkeeper
	new_player = new Forward(1, ++number);
	team1.push_back(new_player);
	new_player = new Forward(1, ++number);
	team1.push_back(new_player);
	new_player = new Forward(1, ++number);
	team1.push_back(new_player);
	new_player = new HalfBack(1, ++number);
	team1.push_back(new_player);
	new_player = new FullBack(1, ++number);
	team1.push_back(new_player);
	new_player = new FullBack(1, ++number);
	team1.push_back(new_player);
	new_player = new GoalKeeper(1, ++number);
	team1.push_back(new_player);
	// same for team2
	number = 0;
	new_player = new Forward(2, ++number);
	team2.push_back(new_player);
	new_player = new Forward(2, ++number);
	team2.push_back(new_player);
	new_player = new Forward(2, ++number);
	team2.push_back(new_player);
	new_player = new HalfBack(2, ++number);
	team2.push_back(new_player);
	new_player = new FullBack(2, ++number);
	team2.push_back(new_player);
	new_player = new FullBack(2, ++number);
	team2.push_back(new_player);
	new_player = new GoalKeeper(2, ++number);
	team2.push_back(new_player);

	for (Player * player : team1) {
		player->moveTo(random(0, 500), random(0, 500));
		player->setEnergy(random(0, 2501) + 3500);
		player->layer = LAYER_NUMBER_PLAYERS;
		drawables.push_back(player);
	}
	for (Player * player : team2) {
		player->moveTo(random(0, 500), random(0, 500));
		player->setEnergy(random(0, 2501) + 3500);
		player->layer = LAYER_NUMBER_PLAYERS;
		drawables.push_back(player);
	}

	// Girls
	for (int i = 0; i < 5; i++) {
		Girl * new_girl = new Girl();
		new_girl->layer = LAYER_NUMBER_GIRLS;
		girls.push_back(new_girl);
		drawables.push_back(new_girl);
	}

	ref1 = new Referee();
	ref1->layer = LAYER_NUMBER_REFEREES;
	ref1->moveTo(100, 40);

	int center_x, center_y;
	field->getCentre(center_x, center_y);

	assRef1 = new AssReferee();
	assRef1->layer = LAYER_NUMBER_REFEREES;

	assRef2 = new AssReferee();
	assRef2->layer = LAYER_NUMBER_REFEREES;

	drawables.push_back(ref1);
	drawables.push_back(assRef1);
	drawables.push_back(assRef2);

	lights[0] = new Lights(0, 0, 250, PI / 32, -PI / 12, -PI / 2 + PI / 12, PI / 12, PI / 3);
	lights[1] = new Lights(canvas->ActualWidth, 0, 250, PI / 32, -PI / 2 - PI / 8, -PI + PI / 8, PI / 12, PI / 3);
	lights[0]->layer = LAYER_NUMBER_LIGHTS;
	lights[1]->layer = LAYER_NUMBER_LIGHTS;
	drawables.push_back(lights[0]);
	drawables.push_back(lights[1]);

	time = 0;
	team1_score = 0;
	team2_score = 0;
	gameState = sStop;
	position0();
	// drawAll() no need, called from our canvas
}

void GameManager::render()
{
	this->render_target_session = gameManager->render_target->CreateDrawingSession();
	render_target_session->Clear(Colors::Transparent);

	set<int> layers;
	for (Drawable* drawable : drawables) {
		layers.insert(drawable->layer);
	}

	// set is automatically ordered from min to max, just as we need
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
	delete render_target_session;
}

void GameManager::moveAll()
{
	if (gameState == sPause) {
		for (Girl*girl : girls) {
			girl->move();
		}
		lights[0]->move();
		lights[1]->move();
		return;
	}

	for (int i = 0; i < 7; i++) {
		team1.at(i)->move();
		team2.at(i)->move();
	}
	ball->move();
	spotlight->move();
	ref1->move();
	assRef1->move();
	assRef2->move();
}

void GameManager::calculateEnergy()
{
	team1_energy = 0;
	team2_energy = 0;

	for (Player * p : team1) {
		team1_energy += p->getEnergy();
	}
	for (Player * p : team2) {
		team2_energy += p->getEnergy();
	}
}

void GameManager::startGame()
{
	int center_x, center_y;
	field->getCentre(center_x, center_y);

	ball->moveTo(center_x, center_y);
	ball->setSpeed(0);


	assRef1->moveTo(center_x, field->getBorderW() / 2 + 2);
	assRef2->moveTo(center_x, field->getH() + 1.5*field->getBorderW() - 2);

	for (int i = 0; i < 5; ++i) {
		girls[i]->moveTo(center_x - 2 * 6 + i * 6, 4);
	}

	if (rand() % 2) {
		position1();
	}
	else {
		position2();
	}

	//sound("whistle.wav", SND_SYNC);
	gameState = sFirstKick;
}

void GameManager::position0()
{
	int y, center_x, center_y;
	field->getCentre(center_x, center_y);

	ref1->moveTo(center_x, center_y - 50);
	ball->moveTo(center_x, center_y - 45);
	assRef1->moveTo(center_x - 10, center_y - 50);
	assRef2->moveTo(center_x + 10, center_y - 50);

	y = center_y - 10 * team1.size() / 2;
	for (int i = 0; i < team1.size(); i++)
	{
		team1[i]->moveTo(center_x - 20, y);
		y += 10;
	}
	y = center_y - 10 * team2.size() / 2;
	for (int i = 0; i < team2.size(); i++)
	{
		team2[i]->moveTo(center_x + 20, y);
		y += 10;
	}

	for (int i = 0; i<5; ++i) girls[i]->moveTo(center_x - 2 * 6 + i * 6, 4);
}

void GameManager::position1()
{
	int center_x, center_y;
	field->getCentre(center_x, center_y);
	ref1->moveTo(center_x + 50, center_y - 50);
	team1[0]->moveTo(center_x - 5, center_y);

	//TODO refactor to foreach
	for (int i = 1; i < team1.size(); i++)
	{
		if (!team1[i]->inGame) continue;
		if (team1[i]->type == tGoalKeeper) team1[i]->moveTo(field->fieldRect->Left, center_y);
		else team1[i]->moveTo(center_x - rand() % (field->getW() / 2 - 30), rand() % (field->getH() - 20) + 20);
	}

	for (int i = 0; i < team2.size(); i++)
	{
		if (!team2[i]->inGame) continue;
		if (team2[i]->type == tGoalKeeper) team2[i]->moveTo(field->fieldRect->Right, center_y);
		else team2[i]->moveTo(center_x + rand() % (field->getW() / 2 - 30), rand() % (field->getH() - 20) + 20);
	}
}

void GameManager::position2()
{
	int center_x, center_y;
	field->getCentre(center_x, center_y);
	ref1->moveTo(center_x - 50, center_y - 50);
	for (int i = 0; i < team1.size(); i++)
	{
		if (!team1[i]->inGame) continue;
		if (team1[i]->type == tGoalKeeper) team1[i]->moveTo(field->fieldRect->Left, center_y);
		else team1[i]->moveTo(center_x - rand() % (field->getW() / 2 - 30), rand() % (field->getH() - 20) + 20);
	}

	team1[0]->moveTo(center_x + 5, center_y);
	for (int i = 1; i < team2.size(); i++)
	{
		if (!team2[i]->inGame) continue;
		if (team2[i]->type == tGoalKeeper) team2[i]->moveTo(field->fieldRect->Right, center_y);
		else team2[i]->moveTo(center_x + rand() % (field->getW() / 2 - 30), rand() % (field->getH() - 20) + 20);
	}
}

void GameManager::tick()
{
	//done = false;
	++time;

	int center_x, center_y, ball_x, ball_y;
	field->getCentre(center_x, center_y);
	ball->getCoord(ball_x, ball_y);

	//drawAll();

	switch (gameState) {
	case sGoal:
		sound_queue.push(Whistle);
		sound_queue.push(Mencheer);
		if (isGirlsAllowed) {
			gameState = sPause;
			lights[0]->on = lights[1]->on = true;
			isLoopSound = true;
			sound_queue.push(SuccessTada);
		}
		else {
			gameState = sRestartGame;
		}
		return;
	case sRestartGame:
		isLoopSound = false;
		// No need for delay
		//::Sleep(1000);
		//for (int i = 0; i<5; ++i) girl[i]->moveTo(xc - 2 * 6 + i * 6, 4);
		lights[0]->on = lights[1]->on = false;
		sound_queue.push(Whistle);
		gameState = sFirstKick;
		return;

	}

	if (field->isGoalLeft(ball_x, ball_y))
	{
		team2_score++;
		gameState = sGoal;
		ball->moveTo(center_x, center_y);
		ball->setSpeed(0);
		position1();
		return;
	}

	if (field->isGoalRight(ball_x, ball_y))
	{
		team2_score++;
		gameState = sGoal;
		ball->moveTo(center_x, center_y);
		ball->setSpeed(0);
		position2();
		return;
	}
	
	moveAll();

	calculateEnergy();
}
