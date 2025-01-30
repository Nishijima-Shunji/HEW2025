#pragma once
#include "Object.h"
class Darkness : public Object
{
private:
	bool flg = true;
public:
	void Update();
	bool GetFlg() { return flg; };
};

