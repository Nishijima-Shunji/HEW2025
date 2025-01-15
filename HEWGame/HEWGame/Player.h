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



	int X = 3;
	int Y = 4;
	int Goal_X = 5;
	int Goal_Y = 8;
	float deltaTime = 0.1f;

	bool Vertical;	//�����ړ�
	bool Horizontal;//�����ړ�

	int MoveList[18][32];

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	void Uninit();

	void SetUp();
	void Move();
	void Animation();

	void DebugList();
};