#pragma once
#include "Object.h"
class Bubble : public Object
{
private:
	float speed;
public:
	void Update();
	void SetSpeed(float);
};

