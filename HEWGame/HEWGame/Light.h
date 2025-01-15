#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;

	std::vector<int>Lightpos_X = {};
	std::vector<int>Lightpos_Y = {};

	bool LightOn = false;
	bool Stop = false;

	int Direction = 0;	//���C�g����	0�F��@1�F���@2�F�E�@3�F��
	int Old_Pos_X = 0;	//�ړ��O���W�FX
	int Old_Pos_Y = 0;	//�ړ��O���W�FY
	int Pos_X = 0;		//�ړ�����W�FX
	int Pos_Y = 0;		//�ړ�����W�FY
	int Count = 0;
	int Number = 0;

public:
	//�}�b�v�f�[�^�̍X�V
	std::vector<std::vector<int>> MapUpdate();
	void DebugMap();
	
	//���C�g�̍X�V
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	
	//�X�V�̃p�[�c���S
	//���C�g�̕ύX
	void Change();
	//���C�g���W�̎擾
	void Position();
	//�ړ�����
	void Move();
	//��������
	void Flash();
	//

};

