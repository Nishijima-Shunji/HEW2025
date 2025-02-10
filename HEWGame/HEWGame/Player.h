#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Player : public Object
{
private:
    int targetX, targetY; // �ړ���̃}�X���W

	int X;
	int Y;
	int Goal_X;
	int Goal_Y;

	bool Start = false;
	bool Vertical;	//�����ړ�
	bool Horizontal;//�����ړ�
	bool Reverse;	//���]

	int MoveList[18][32];

	bool goalFlg = false;

	int framecount;
	int animcount;

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	//void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>,GameScene&);
	//void Uninit();

	bool GetFlg() { return goalFlg; };
	void SetUp();
	void Move();
	void Animation();

	void DebugList();
};