#pragma once
#include "Object.h"
#include "TextureManager.h"

class Bubble : public Object
{
private:
	float speed;
public:
	void Update();
	void SetSpeed(float);
	float GetPosY();
};

