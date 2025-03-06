#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs


class Mendako : public Object
{
private:

    float x, y;        // �������W�i�A�j���[�V�����p�j
    int targetX, targetY; // �ړ���̃}�X���W
    float speed;       // �ړ����x

	

	bool Men_hit = false;//�����_�R���������������ׂ�
	int Mendako_C;//�����_�R�擾��
	
	int frameCounter = 0;


	int framecount;
	int animcount;
	int state = 0;
	int animTimer = 0;
	bool menAlive = true;//�����_�R�̐�����

	enum AnimationState {
		WAITING,       // �ʏ�ҋ@�A�j���[�V����
		ANIM   // ����̃A�j���[�V����
	};

	

public:

	bool menGk =true;
	
	bool GetFg_men() { return menAlive;};
	bool GetMendakoCount() { return Mendako_C; };
	void Init();
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>, GameScene& game);
	void Uninit();

	void Catch();//�����_�R�擾
	

	
};