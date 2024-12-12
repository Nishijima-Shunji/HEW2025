#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;

	std::vector<int>Lightpos_X = {};
	std::vector<int>Lightpos_Y = {};


	bool LightOn = false;

	int Mode = 0;

	int Old_Pos_X = 0;
	int Old_Pos_Y = 0;
	int Pos_X = 0;
	int Pos_Y = 0;
	int Count = 0;
	int Number = 0;

public:

	Light();
	~Light();

	//マップデータの更新
	std::vector<std::vector<int>> MapUpdate();
	void DebugMap();
	
	//ライトの更新
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	
	//更新のパーツ分担
	//ライトの変更
	void Change();
	//ライト座標の取得
	void Position();
	//移動処理
	void Move();
	//発光処理
	void Flash();
	//

};

