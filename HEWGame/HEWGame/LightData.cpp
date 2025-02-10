#include "LightData.h"

int lightNumber = 0;
int nowlight = 0;
int oldlight = 0;

struct Shelter {
	bool data = false;
	int Light_Pos_X = 0;
	int Light_Pos_Y = 0;
	int Light_Old_Pos_X = 0;
	int Light_Old_Pos_Y = 0;

};

Shelter dataShelter;

void LightDataReset()
{
	lightNumber = 0;
	nowlight = 0;
	oldlight = 0;
	dataShelter.data = false;
}