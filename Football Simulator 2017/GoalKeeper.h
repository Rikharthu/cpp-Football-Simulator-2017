#pragma once
#include "Player.h"

class GoalKeeper :public Player {

public:
	GoalKeeper(int t, int n);
	void move();
	void kick();
};