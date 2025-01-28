#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Mendako : public Object
{
private:

    float x, y;        // 実数座標（アニメーション用）
    int targetX, targetY; // 移動先のマス座標
    float speed;       // 移動速度

	bool menAlive = true;//メンダコの生存状況

	bool Men_hit = false;//メンダコが当たったか調べる
	int Mendako_C;//メンダコ取得数
	
	int frameCounter = 0;


	int framecount;
	int animcount;
	int state = 0;
	int animTimer = 0;

	enum AnimationState {
		WAITING,       // 通常待機アニメーション
		ANIM   // 特定のアニメーション
	};

	

public:

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	void Uninit();

	void MendakoPos();
	void Catch();
	
};