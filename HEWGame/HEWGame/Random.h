#pragma once
#include <random>

//�����G���W��
class RandomGene
{
private:
	std::random_device rd; // �񌈒�I�ȗ������� 
	std::mt19937 gen; // �����Z���k�E�c�C�X�^�����G���W��
	std::uniform_int_distribution<int> dis; // ��l���z

public:
	RandomGene(int min, int max) :
		rd(), gen(rd()), dis(min, max) {};

	RandomGene(float min, float max) :
		rd(), gen(rd()), dis(min, max) {};

	int Int_generate() {
		return dis(gen);
	}

	float Float_generate() {
		return dis(gen);
	}
};