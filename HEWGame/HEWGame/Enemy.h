#pragma once
#include "Object.h"

#define E_UP	(0)
#define E_RIGHT	(1)
#define E_DOWN	(2)
#define E_LEFT	(3)

#define WIDTH	(32)
#define HEIGHT	(18)

#define NOTHING		(0)
#define STOP_MOVE	(1)
#define STOP_CHECK	(2)

class Enemy : public Object
{
private:
	int targetX;
	int targetY;

	int speed = 1.0f;

	bool move = false;
	int direction = E_UP;
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
	int CheckAllDirection(int pos_x, int pos_y, int dire);
	void DirectionCase(int dire);
	void CheckDead(GameScene&);
	void Animation();
};


