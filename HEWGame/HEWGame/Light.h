#pragma once

#include "Object.h"


#include <vector>
#include <iostream>

class Light : public Object
{
private:

public:
	void Init();
	void Update(std::vector<int>);
	void Draw();
	void Uninit();

};

