#pragma once
#include "Player.h"

class FullBack :public Player {
protected:
	FullBack(int t, int n);
	virtual void move();
	virtual void kick();
};