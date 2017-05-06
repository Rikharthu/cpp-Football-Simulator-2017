#include "pch.h"
#include "Forward.h"
#include "GameManager.h"


Forward::Forward(int t, int n) :Player(t, n)
{
	speed = 12;
	area = *(gameManager->field->fieldRect);
	type=tForward;
}