#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Player : public Object
{
private:
    float x, y;        // 実数座標（アニメーション用）
    int targetX, targetY; // 移動先のマス座標
    float speed;       // 移動速度



	int X = 3;
	int Y = 4;
	int Goal_X = 5;
	int Goal_Y = 8;
	float deltaTime = 0.1f;

	bool Vertical;	//垂直移動
	bool Horizontal;//水平移動

	int MoveList[18][32];

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	void Uninit();

	void SetUp();
	void Move();
	void Animation();

	void DebugList();
};