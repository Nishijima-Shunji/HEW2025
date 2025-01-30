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

	//‰Eã‚©‚ç‰½ŒÂ–Ú‚ğØ‚è”²‚¢‚Ä•\¦‚·‚é‚©
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>> , GameScene&);
	void Uninit();

};