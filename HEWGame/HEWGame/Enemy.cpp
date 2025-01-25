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
	lightX = false;
	lightY = false;
	if (targetX != PosX) {
		// �������Ƀ��C�g�����邩
		for (int tempX = PosX; tempX > 0; tempX--) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
			}
		}
		// �E�����Ƀ��C�g�����邩
		for (int tempX = PosX; tempX < 32; tempX++) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
			}
		}
	}

	if (targetY != PosY) {
		// ������Ƀ��C�g�����邩
		for (int tempY = PosY; tempY > 0; tempY--) {
			if (Map[tempY][PosX] == 20) {
				targetY = tempY;
				lightY = true;
				moveY = true;
			}
		}
		// �������Ƀ��C�g�����邩
		for (int tempY = PosY; tempY < 18; tempY++) {
			if (Map[tempY][PosX] == 20) {
				targetY = tempY;
				lightY = true;
				moveY = true;
			}
		}
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
		if (pos.x == nextPosX * 30.0f) {
			PosX = nextPosX;
			Map[PosY][PosX + 1] = 0;
			Map[PosY][PosX] = 3;
			move = false;
		}
	}
	else if (moveY) {

	}
}