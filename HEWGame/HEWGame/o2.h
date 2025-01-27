#pragma once
#include "Object.h"
#include "Player.h"

class O2 : public Object
{
private:
	int state = 0;
	float velocityX;
	float velocityY;
	float gravity = 0.98;
	bool init = false;

public:
	void Update();
	int GetState() { return state; };
	void SetState(int s_state) { state = s_state; };
};

