#pragma once
#include "Object.h"

class Enemy : public Object
{
private:
	int targetX;
	int targetY;

	int speed = 1.0f;

	int move = 0;
	bool movingToTarget = false;
	bool moveX;
	bool moveY;
	bool prevlight = false;
	int nextPosX;
	int nextPosY;
	int direction = 0;
	bool inLight = false;
	bool hasFoundLightBefore = false;  // 一度でもライトを見つけたか
	bool hasReachedTarget = false;		// 到着フラグ
	int framecount;
	int animcount;

	bool state = false;
	bool animationEnd = false;

public:
	Enemy();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>,GameScene&);

	void FindLight();
	void Move();
	int GetFlg() { return animationEnd; };
	void CheckDead(GameScene&);
	void Animation();
};


