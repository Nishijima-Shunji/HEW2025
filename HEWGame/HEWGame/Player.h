#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Player : public Object
{
private:
    int targetX, targetY; // �ړ���̃}�X���W

	int height, width;
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

	int moveState = 0;
	enum class MoveState {
		Stop,
		Move,
		isTrap
	};

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
	void SetMoveState(int);
	void Animation(GameScene& game);
	void CheckEdge();
	void CheckDistance(std::vector<std::vector<int>> Map, int , int );
};