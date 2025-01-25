#pragma once
#include "Object.h"
class O2 : public Object
{
private:
	int state = 0;
	float gravity = 0.98;

public:
	void Update();
	void SetState(int s_state) { state = s_state; };
};

