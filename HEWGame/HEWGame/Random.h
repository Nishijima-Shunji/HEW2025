#pragma once
#include <random>

//乱数エンジン
class RandomGene
{
private:
	std::random_device rd; // 非決定的な乱数生成 
	std::mt19937 gen; // メルセンヌ・ツイスタ乱数エンジン
	std::uniform_int_distribution<int> dis; // 一様分布

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