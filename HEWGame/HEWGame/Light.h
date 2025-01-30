#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;

	std::vector<int>Lightpos = {};
	int Gimmick[18][32];

	bool SetUp	 = false;
	bool LightOn = false;
	bool Stop	 = false;

	int Direction = 0;	//���C�g����	0�F��@1�F���@2�F�E�@3�F��
	//�v�C���F��Object.h��direction������
	int Old_Pos_X = 0;	//�ړ��O���W�FX
	int Old_Pos_Y = 0;	//�ړ��O���W�FY
	int Pos_X = 0;		//�ړ�����W�FX
	int Pos_Y = 0;		//�ړ�����W�FY
	int Number = 1;		//���C�g�i���o�[
	int LightMAX = 0;

public:
	//�}�b�v�f�[�^�̍X�V
	std::vector<std::vector<int>> MapUpdate();
	void DebugMap();

	//���C�g�̍X�V
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>, GameScene&);

	//�X�V�̃p�[�c���S
	// 
	void SetGimmick();
	//���C�g�̕ύX
	void Change();
	//���C�g���W�̎擾
	void Position();
	//�ړ�����
	void Move();
	//��]����
	void Spin();
	//��������
	void Flash();
	//
	void FlashSpace();
	//
	void FlashGimmick();
	//
	void Reflection(int);
};



