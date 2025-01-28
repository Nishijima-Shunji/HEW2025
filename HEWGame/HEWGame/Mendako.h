#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Mendako : public Object
{
private:
	int framecount;
	int animcount;
	int state = 0;
	int animTimer = 0;

	enum AnimationState {
		WAITING,       // 通常待機アニメーション
		ANIM   // 特定のアニメーション
	};

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
};