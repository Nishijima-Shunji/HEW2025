#pragma once
#include "Object.h"

#define UP		(0)
#define DOWN	(1)
#define LEFT	(2)
#define RIGHT	(3)

#define WIDTH	(32)
#define HEIGHT	(18)

class Enemy : public Object
{
private:
	int targetX;
	int targetY;

	int speed = 1.0f;

	bool move = false;
	int direction = UP;
	bool inLight = false;
	int framecount;
	int animcount;

	bool state = false;
	bool animationEnd = false;

	void FindLight();
	void Move();

public:
	Enemy();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>,GameScene&);

	int GetFlg() { return animationEnd; };
	void CheckDead(GameScene&);
	void Animation();
};


