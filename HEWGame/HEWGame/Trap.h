#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Trap : public Object
{
private:
	int framecount;
	int animcount;

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>> , GameScene&);
	void Uninit();

};