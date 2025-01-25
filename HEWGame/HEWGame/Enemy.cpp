#include "Enemy.h"


std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData)
{
	Map = MapData;

	// �}�b�v�̈ʒu�f�[�^����Enemy�̈ʒu���擾
	//FindEnemyPos();

	// �ړ����T��
	if (!move) {
		moveX = false;
		moveY = false;
		FindLight();

		// �c�ړ��Ɖ��ړ��̋������Z�����ֈړ�
		if (lightX && lightY) {
			if (abs(targetX - PosX) < abs(targetY - PosY)) {
				moveY = false;
				move = true;
			}
			else if (abs(targetX - PosX) > abs(targetY - PosY)) {
				moveX = false;
				move = true;
			}
		}
	}

	Move();

	return Map;
}

void Enemy::FindEnemyPos() {
	// Enemy�̍��W���擾
	auto Enemypos = findCoordinate(Map, 3);
	for (const auto& coord : Enemypos) {
		PosX = coord.first;
		PosY = coord.second;
	}
}

void Enemy::FindLight() {
	static bool foundLight = false; // ���C�g����x��������L������
	lightX = false;
	lightY = false;

	if (targetX != PosX) {
		for (int tempX = PosX; tempX > 0; tempX--) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
				foundLight = true; // ���C�g�������L�^
			}
		}
		for (int tempX = PosX; tempX < 32; tempX++) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
				foundLight = true; // ���C�g�������L�^
			}
		}
	}

	if (targetY != PosY) {
		for (int tempY = PosY; tempY > 0; tempY--) {
			if (Map[tempY][PosX] == 20) {
				targetY = tempY;
				lightY = true;
				moveY = true;
				foundLight = true;
			}
		}
		for (int tempY = PosY; tempY < 18; tempY++) {
			if (Map[tempY][PosX] == 20) {
				targetY = tempY;
				lightY = true;
				moveY = true;
				foundLight = true;
			}
		}
	}

	// ���C�g��������Ȃ��Ă��A�ȑO�̃^�[�Q�b�g�Ɍ�����
	if (!lightX && !lightY && foundLight) {
		moveX = (PosX != targetX);
		moveY = (PosY != targetY);
	}
}

void Enemy::Move() {
	if (moveX) {
		if ((PosX - targetX) > 0) {
			nextPosX = PosX - 1;
			if (Map[PosY][nextPosX] != WALL) {
				pos.x -= 1.0f;
			}
		}
		else {
			nextPosX = PosX + 1;
			if (Map[PosY][nextPosX] != 3) {
				pos.x += 1.0f;
			}
		}

		// �ڕW�n�_�ɓ��B�������~
		if (pos.x == nextPosX * 30.0f) {
			PosX = nextPosX;
			Map[PosY][PosX + 1] = 0;  // ���̈ʒu���N���A
			Map[PosY][PosX] = 3;       // �V�����ʒu���X�V
			move = false;
			movingToTarget = false;    // �ڕW�ɓ��B�����̂ňړ��t���O�����Z�b�g
		}
	}
	else if (moveY) {
		// Y�����̈ړ������i���l�ɓK�p�j
	}

	std::cout << moveX << std::endl;
}
