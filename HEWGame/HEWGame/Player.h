#pragma once

#include "Object.h"

#include <iostream>
#include <cmath> // std::abs

#define P_UP	(0)
#define	P_RIGHT	(1)
#define P_DOWN	(2)
#define P_LEFT	(3)

#define NOTHING		(0)
#define STOP_MOVE	(1)
#define STOP_CHECK	(2)

class Player : public Object
{
private:
    int targetX, targetY; // �ړ���̃}�X���W
	int holdDire = P_UP;

	int speed = 1.0f;

	//�����ړ�,�����ړ�
	bool Vertical = false, Horizontal = false;
	bool goalFg = false;
	bool move = false;

	int MapList[18][32];

	int framecount;
	int animcount;

	void PlayerMove();
	void CheckMove();
	bool CheckGimmic();
	void Reflection(int gimmic);
	void Stream(int gimmic);
	bool CheckMap(int pos_y, int pos_x, int dire);
	void DirectionCase(int dire);
	void MovePlayer();

public:

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	void Init(std::vector<std::vector<int>> MapData);
	std::vector<std::vector<int>> Update(std::vector<std::vector<int>>,GameScene&);

	bool GetFg() { return goalFg; };
};