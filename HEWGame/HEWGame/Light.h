#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;

	std::vector<int>Lightpos = {};

	bool SetUp	 = false;
	bool LightOn = false;
	bool Stop	 = false;

	int Direction = 0;	//ライト方向	0：上　1：下　2：右　3：左
	int Old_Pos_X = 0;	//移動前座標：X
	int Old_Pos_Y = 0;	//移動前座標：Y
	int Pos_X = 0;		//移動後座標：X
	int Pos_Y = 0;		//移動後座標：Y
	int Number = 1;		//ライトナンバー
	int LightMAX = 0;

public:
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
};



