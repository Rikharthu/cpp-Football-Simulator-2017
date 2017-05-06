#pragma once
#include "Human.h"


// Referee that moves only along Y axis
class AssReferee : public Human
{
public:
	AssReferee();
	void move();
};
