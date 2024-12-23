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

	int newX;
	int newY;
	float deltaTime;

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	void Uninit();
};