#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Mendako : public Object
{
private:
	int framecount;
	int animcount;
	int state = 0;
	int animTimer = 0;

	enum AnimationState {
		WAITING,       // �ʏ�ҋ@�A�j���[�V����
		ANIM   // ����̃A�j���[�V����
	};

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
};