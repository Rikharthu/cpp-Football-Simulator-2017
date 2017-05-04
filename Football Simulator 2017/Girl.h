#pragma once
#include "Human.h"

class Girl :public Human
{
public:
	Girl();
	virtual void move();
	virtual void draw();
};