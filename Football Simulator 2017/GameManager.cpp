#include "pch.h"
#include "GameManager.h"

// TODO

GameManager::GameManager(CanvasCommandList ^cl)
{
	this->field_cl = cl;
}

void GameManager::init()
{
	this->field = new Field();
	this->render_target = ref new CanvasRenderTarget(this->canvas,this->canvas->Size);
}
