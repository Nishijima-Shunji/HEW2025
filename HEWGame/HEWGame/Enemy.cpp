#include "Enemy.h"

std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData)
{
	Map = MapData;

	if (!move) {
		FindLight();
	}

	Move();

	// ������ɒT�����ĊJ
	if (PosX == targetX && PosY == targetY) {
		hasReachedTarget = true;
	}

	// �ҋ@�A�j���[�V����
	SetUV(animcount % 8, (animcount / 8) % 2);
	if (framecount % 5 == 0) {
		animcount++;
	}
	framecount++;

	return Map;
}

void Enemy::FindLight() {
	if (move) return;  // �ړ����͒T�����s��Ȃ�

	lightX = false;
	lightY = false;
	bool foundLight = false;

	// X�����Ɍ���T��
	for (int tempX = PosX - 1; tempX >= 0; tempX--) {
		if (Map[PosY][tempX] == Luminous) {
			targetX = tempX;
			lightX = true;
			moveX = true;
			foundLight = true;
			break;
		}
	}

	for (int tempX = PosX + 1; tempX < 32; tempX++) {
		if (Map[PosY][tempX] == Luminous) {
			targetX = tempX;
			lightX = true;
			moveX = true;
			foundLight = true;
			break;
		}
	}

	// Y�����Ɍ���T��
	for (int tempY = PosY - 1; tempY >= 0; tempY--) {
		if (Map[tempY][PosX] == 20) {
			targetY = tempY;
			lightY = true;
			moveY = true;
			foundLight = true;
			break;
		}
	}

	for (int tempY = PosY + 1; tempY < 18; tempY++) {
		if (Map[tempY][PosX] == 20) {
			targetY = tempY;
			lightY = true;
			moveY = true;
			foundLight = true;
			break;
		}
	}

	if (!foundLight && hasFoundLightBefore) {
		// ���̃}�X�ւ̈ړ�����
		if (moveX) {
			targetX = (PosX > targetX) ? PosX - 1 : PosX + 1;
		}
		if (moveY) {
			targetY = (PosY > targetY) ? PosY - 1 : PosY + 1;
		}
		move = true;
	}
}

void Enemy::Move() {
	if (moveX) {
		// X�����Ɉړ�
		if ((PosX - targetX) > 0) {
			nextPosX = PosX - 1;
			if (Map[PosY][nextPosX] != WALL) {
				pos.x -= 1.0f;
			}
		}
		else {
			nextPosX = PosX + 1;
			if (Map[PosY][nextPosX] != WALL) {
				pos.x += 1.0f;
			}
		}

		if (std::abs(pos.x - nextPosX * 30.0f) < 0.1f) {
			// �ړI�n���v���C���[(2)�Ȃ�state��1�ɂ���
			if (Map[PosY][nextPosX] == P_DIVER) {
				state = true;
			}
			PosX = nextPosX;
			Map[PosY][PosX] = 3;
			move = false;

			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
			targetX = PosX;
			moveX = false;  // X�����ɂ���ȏ�ړ����Ȃ�
		}
	}

	if (moveY) {
		// Y�����Ɉړ�
		if ((PosY - targetY) > 0) {
			nextPosY = PosY - 1;
			if (Map[nextPosY][PosX] != WALL) {
				pos.y += 1.0f;
			}
		}
		else {
			nextPosY = PosY + 1;
			if (Map[nextPosY][PosX] != WALL) {
				pos.y -= 1.0f;
			}
		}

		if (std::abs(pos.y - (nextPosY * -30.0f)) < 0.1f) {
			// �ړI�n���v���C���[(2)�Ȃ�state��1�ɂ���
			if (Map[nextPosY][PosX] == P_DIVER) {
				state = true;
			}
 			PosY = nextPosY;
			Map[PosY][PosX] = 3;
			move = false;

			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
			targetY = PosY;
			moveY = false;  // Y�����ɂ���ȏ�ړ����Ȃ�
		}
	}
}

//void Enemy::Move() {
//	if (moveX) {
//		// X�����Ɉړ�
//		if (moveRight) {
//			nextPosX = PosX + 1;
//			if (Map[PosY][nextPosX] != WALL) {
//				pos.x += 1.0f;
//			}
//			else {
//				// �ǂɓ��B����������𔽓]
//				moveRight = false;
//				moveLeft = true;
//			}
//		}
//		else if (moveLeft) {
//			nextPosX = PosX - 1;
//			if (Map[PosY][nextPosX] != WALL) {
//				pos.x -= 1.0f;
//			}
//			else {
//				// �ǂɓ��B����������𔽓]
//				moveRight = true;
//				moveLeft = false;
//			}
//		}
//
//		if (std::abs(pos.x - nextPosX * 30.0f) < 0.1f) {
//			// �ړI�n���v���C���[(2)�Ȃ�state��true�ɂ���
//			if (Map[PosY][nextPosX] == P_DIVER) {
//				state = true;
//			}
//			PosX = nextPosX;
//			Map[PosY][PosX] = 3;
//			move = false;
//
//			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
//			targetX = PosX;
//		}
//	}
//
//	if (moveY) {
//		// Y�����Ɉړ�
//		if (moveUp) {
//			nextPosY = PosY - 1;
//			if (Map[nextPosY][PosX] != WALL) {
//				pos.y -= 1.0f;
//			}
//			else {
//				// �ǂɓ��B����������𔽓]
//				moveUp = false;
//				moveDown = true;
//			}
//		}
//		else if (moveDown) {
//			nextPosY = PosY + 1;
//			if (Map[nextPosY][PosX] != WALL) {
//				pos.y += 1.0f;
//			}
//			else {
//				// �ǂɓ��B����������𔽓]
//				moveUp = true;
//				moveDown = false;
//			}
//		}
//
//		if (std::abs(pos.y - (nextPosY * -30.0f)) < 0.1f) {
//			// �ړI�n���v���C���[(2)�Ȃ�state��true�ɂ���
//			if (Map[nextPosY][PosX] == P_DIVER) {
//				state = true;
//			}
//			PosY = nextPosY;
//			Map[PosY][PosX] = 3;
//			move = false;
//
//			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
//			targetY = PosY;
//		}
//	}
//}



