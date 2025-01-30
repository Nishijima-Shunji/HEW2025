#pragma once
#include "Object.h"

class Wall : public Object
{
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>, GameScene&);
};

