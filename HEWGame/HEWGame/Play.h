#pragma once
#include <vector>
#include <iostream>

#include "Input.h"
#include "StageObjDefine.h"

#define NODATA	(-9)
#define KARI	(99999)
#define WIDTH	(32)
#define HEIGHT	(18)

#define NEUTRAL		(0)
#define NOTLIGHTUP	(-1)

#define UP		(0)
#define DOWN	(1)
#define RIGHT	(2)
#define LEFT	(3)

class Play
{
private:
	int width = 0, height = 0;
	int direction = 0, old_direction;
	int old_pos_x, old_pos_y, new_pos_x, new_pos_y;
	int light_number = 0, light_max = 0;
	int Gimmick[HEIGHT][WIDTH];
	int LightUpMap[HEIGHT][WIDTH];

	std::vector<int> LightPos_x, LightPos_y,keep_pos_x, keep_pos_y, Direction, keep_Direction;
	std::vector<bool> LightOn, LightStop, keepLightOn;
	std::vector<std::vector<int>> Map;

	Input input;

	void CheckEdge();
	void CheckLight();
	void SetGimmick();
	void SetLightUpMap();

	void ChangeLight();
	void MoveLight();
	void LightUp();
	bool Flash(const int pos_x, const int pos_y, 
		const bool light_on, const int nowlight);
	void Reflection(const int pos_x, const int pos_y, const int nowlight);

	void MapUpdate();
	void DebugMap();

public:
	void Init(std::vector<std::vector<int>> MapList);
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>> MapList);
	void Uninit();
};