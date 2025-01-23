#pragma once
#include "Object.h"

class Enemy : public Object
{
private:
	int targetX;
	int targetY;

	int move;
	bool moveX;
	bool moveY;
	bool lightX;
	bool lightY;
	int nextPosX;
	int nextPosY;

public:
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);

	void FindEnemyPos();
	void FindLight();
	void Move();
};


