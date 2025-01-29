#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Player : public Object
{
private:
    float x, y;        // �������W�i�A�j���[�V�����p�j
    int targetX, targetY; // �ړ���̃}�X���W
    float speed;       // �ړ����x



	int X;
	int Y;
	int Goal_X;
	int Goal_Y;
	float deltaTime = 0.1f;

	bool Vertical;	//�����ړ�
	bool Horizontal;//�����ړ�
	bool Reverse;	//���]

	int MoveList[18][32];

	int framecount;
	int animcount;

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	//void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	//void Uninit();

	void SetUp();
	void Move();
	void Animation();

	void DebugList();
};