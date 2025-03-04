#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Player : public Object
{
private:
    int targetX, targetY; // 移動先のマス座標

	int height, width;
	int X;
	int Y;
	int Goal_X;
	int Goal_Y;

	bool Start = false;
	bool Vertical;	//垂直移動
	bool Horizontal;//水平移動
	bool Reverse;	//反転

	int MoveList[18][32];

	bool goalFlg = false;

	int framecount;
	int animcount;

	int moveState = 0;
	enum class MoveState {
		Stop,
		Move,
		isTrap
	};

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	//void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>,GameScene&);
	//void Uninit();

	bool GetFlg() { return goalFlg; };
	void SetUp();
	void Move();
	void SetMoveState(int);
	void Animation(GameScene& game);
	void CheckEdge();
	void CheckDistance(std::vector<std::vector<int>> Map, int , int );
};