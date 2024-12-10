#pragma once

#include "Object.h"

#include <vector>
#include <iostream>

class Light : public Object
{
private:
	int Width = 0;
	int Height = 0;
	std::vector<std::vector<int>> Map = {};

	std::vector<int>Lightpos_X = {};
	std::vector<int>Lightpos_Y = {};

	int Mode = 0;

	int Old_Pos_X = 0;
	int Old_Pos_Y = 0;
	int Pos_X = 0;
	int Pos_Y = 0;
	int Count = 0;
	int Number = 1;

public:

	Light();
	~Light();

	//�}�b�v�f�[�^�̍X�V
	std::vector<std::vector<int>> MapUpdate(std::vector<std::vector<int>>);
	
	//���C�g�̍X�V
	void Update(int,int, std::vector<std::vector<int>>);
	
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

