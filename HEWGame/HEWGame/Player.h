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

	int newX;
	int newY;
	float deltaTime;

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	void Uninit();
};