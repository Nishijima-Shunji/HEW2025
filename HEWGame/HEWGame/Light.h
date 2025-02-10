#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

#define NODATA	(-9)
#define KARI	(99999)
#define WIDTH	(32)
#define HEIGHT	(18)

#define UP		(0)
#define DOWN	(1)
#define RIGHT	(2)
#define LEFT	(3)

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;

	//std::vector<int>Lightpos = {};
	//std::vector<int>LightDirection;
	int Gimmick[18][32];

	bool SetUp	 = false;
	bool LightOn = false;
	bool Stop	 = true;

	int Direction = 1;	//ライト方向	0：上　1：下　2：右　3：左
	int old_Direction = 0;
	//要修正：↑Object.hにdirectionがある
	int Old_Pos_X = 0;	//移動前座標：X
	int Old_Pos_Y = 0;	//移動前座標：Y
	int Pos_X = 0;		//移動後座標：X
	int Pos_Y = 0;		//移動後座標：Y
	int Number = 0;		//ライトナンバー
	int LightMAX = 0;

public:
	//マップデータの更新
	void MapUpdate();
	void DebugMap();

	//ライトの更新
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>, GameScene&);

	//更新のパーツ分担
	// 
	void SetGimmick();
	//ライトの変更
	void Change();
	//ライト座標の取得
	void Position();
	//移動処理
	void Move();
	//回転処理
	void Spin();
	//発光処理
	void Flash();
	//
	void FlashSpace(int _x, int _y);
	//
	void FlashGimmick(int _x, int _y);
	//
	void Reflection(int);
};