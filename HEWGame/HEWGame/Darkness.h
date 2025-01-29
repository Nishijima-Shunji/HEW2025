#pragma once
#include "Object.h"
class Darkness : public Object
{
private:
	bool flg = true;
public:
	bool GetFlg() { return flg; };
};

