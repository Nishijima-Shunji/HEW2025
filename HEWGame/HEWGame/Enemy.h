#pragma once
#include "Object.h"

class Enemy : public Object
{
private:
	int targetX;
	int targetY;

	int move = 0;
	bool movingToTarget = false;
	bool moveX;
	bool moveY;
	bool lightX = false;
	bool lightY = false;
	int nextPosX;
	int nextPosY;
	bool hasFoundLightBefore = false;  // ��x�ł����C�g����������
	bool hasReachedTarget = false;		// �����t���O
	bool movingUp = true;
	int prevObj = 0;
	bool hasStoredPrevTile;

	int framecount;
	int animcount;

	bool state = false;

public:
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);

	void FindLight();
	void Move();
	int GetState() { return state; };
};


