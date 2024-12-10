#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
protected:
	std::vector<int>Lightpos_X;
	std::vector<int>Lightpos_Y;

	int Mode = 0;

	int Old_Pos_X = 0;
	int Old_Pos_Y = 0;
	int Pos_X = 0;
	int Pos_Y = 0;
	int Count;
	int Number = 1;

public:
	Light();

	void Update(int,int, std::vector<std::vector<int>>);
	std::vector<std::vector<int>> Map(std::vector<std::vector<int>>);
};

