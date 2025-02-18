#include "Enemy.h"
#include "GameScene.h"

//����

Enemy::Enemy() {

}

std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	Map = MapData;
	if (!state) {
		if (!move) {
			FindLight();
		}

		Move();

		CheckDead(game);
		// ������ɒT�����ĊJ
		if (PosX == targetX && PosY == targetY) {
			hasReachedTarget = true;
		}

		// �ҋ@�A�j���[�V����
		SetUV(animcount % 8, (animcount / 8) % 2);
		if (framecount % 5 == 0) {
			animcount++;
		}
	}
	else {
		if (!animationEnd) {
			// �T���̊��݂��A�j���[�V����
			Animation();
		}
	}
	framecount++;

	return Map;
}

void Enemy::FindLight() {
	if (move) return;  // �ړ����͒T�����s��Ȃ�
	bool foundLight = false;

	if (Map[PosY][PosX] == LUMINOUS) {
		inLight = true;
	}
	else {
		inLight = false;
	}

	// X�����Ɍ���T��
	for (int tempX = PosX - 1; tempX > 0; tempX--) {
		if (!inLight || direction == LEFT) {
			// �T�����ɕǂ�����΂����ł��̕����͏I��
			if (Map[PosY][tempX] == WALL || Map[PosY][tempX] == LIGHTUPWALL ||
				Map[PosY][tempX] == MAP_END || Map[PosY][tempX] == LIGHT_1) {
				if ((Map[PosY][PosX - 1] == WALL || Map[PosY][PosX - 1] == LIGHTUPWALL ||
					Map[PosY][PosX - 1] == MAP_END || Map[PosY][PosX - 1] == LIGHT_1 
					|| Map[PosY][PosX - 1] == GOAL) 
					&& inLight) {
					direction = RIGHT;
					targetX = tempX;
					moveX = true;
					foundLight = true;
				}

				break;
			}
			// ��������������ړI�n�ݒ�
			if (Map[PosY][tempX] == LUMINOUS) {
				targetX = tempX;
				moveX = true;
				foundLight = true;

				break;
			}
		}
		if (inLight && (Map[PosY - 1][PosX] != LUMINOUS && Map[PosY + 1][PosX] != LUMINOUS) 
			&& !prevlight) {
			direction = RIGHT;
		}
	}
	for (int tempX = PosX + 1; tempX < WIDTH; tempX++) {
		if (!inLight || direction == RIGHT) {
			// �T�����ɕǂ�����΂����ł��̕����͏I��
			if (Map[PosY][tempX] == WALL || Map[PosY][tempX] == LIGHTUPWALL ||
				Map[PosY][tempX] == MAP_END || Map[PosY][tempX] == LIGHT_1) {
				if ((Map[PosY][PosX + 1] == WALL || Map[PosY][PosX + 1] == LIGHTUPWALL ||
					Map[PosY][PosX + 1] == MAP_END || Map[PosY][PosX + 1] == LIGHT_1 || 
					Map[PosY][PosX + 1] == GOAL) 
					&& inLight) {
					direction = LEFT;
					targetX = tempX;
					moveX = true;
					foundLight = true;
				}

				break;
			}
			if (Map[PosY][tempX] == LUMINOUS) {
				targetX = tempX;
				moveX = true;
				foundLight = true;

				break;
			}
		}
		if (inLight && (Map[PosY - 1][PosX] != LUMINOUS && Map[PosY + 1][PosX] != LUMINOUS) 
			&& !prevlight) {
			direction = RIGHT;
		}
	}

	// Y�����Ɍ���T��
	for (int tempY = PosY - 1; tempY > 0; tempY--) {
		if (!inLight || direction == UP) {
			// �T�����ɕǂ�����΂����ł��̕����͏I��
			if (Map[tempY][PosX] == WALL || Map[tempY][PosX] == LIGHTUPWALL ||
				Map[tempY][PosX] == MAP_END || Map[tempY][PosX] == LIGHT_1) {
				if ((Map[PosY - 1][PosX] == WALL || Map[PosY - 1][PosX] == LIGHTUPWALL ||
					Map[PosY - 1][PosX] == MAP_END || Map[PosY - 1][PosX] == LIGHT_1 ||
					Map[PosY - 1][PosX] == GOAL) 
					&& inLight) {
					direction = DOWN;
					targetY = tempY;
					moveY = true;
					foundLight = true;
				}
				break;
			}
			if (Map[tempY][PosX] == LUMINOUS) {
				targetY = tempY;
				moveY = true;
				foundLight = true;
				break;
			}
		}
		if (inLight && (Map[PosY][PosX - 1] != LUMINOUS && Map[PosY][PosX + 1] != LUMINOUS) && 
			!prevlight) {
			direction = DOWN;
		}
	}
	for (int tempY = PosY + 1; tempY < HEIGHT; tempY++) {
		if (!inLight || direction == DOWN) {
			// �T�����ɕǂ�����΂����ł��̕����͏I��
			if (Map[tempY][PosX] == WALL || Map[tempY][PosX] == LIGHTUPWALL ||
				Map[tempY][PosX] == MAP_END || Map[tempY][PosX] == LIGHT_1) {
				if ((Map[PosY + 1][PosX] == WALL || Map[PosY + 1][PosX] == LIGHTUPWALL ||
					Map[PosY + 1][PosX] == MAP_END || Map[PosY + 1][PosX] == LIGHT_1 || 
					Map[PosY + 1][PosX] == GOAL) && inLight) {
					direction = UP;
					targetY = tempY;
					moveY = true;
					foundLight = true;
				}

				break;
			}
			if (Map[tempY][PosX] == LUMINOUS) {
				targetY = tempY;
				moveY = true;
				foundLight = true;

				break;
			}
		}
		if (inLight && (Map[PosY][PosX - 1] != LUMINOUS && Map[PosY][PosX + 1] != LUMINOUS) 
			&& !prevlight) {
			direction = DOWN;
		}
	}

	if (foundLight) {
		// ���̃}�X�ւ̈ړ�����
		if (moveX && PosX != targetX) {
			targetX = (PosX > targetX) ? PosX - 1 : PosX + 1;
		}
		if (moveY && PosY != targetY) {
			targetY = (PosY > targetY) ? PosY - 1 : PosY + 1;
		}
		move = true;
	}
}

void Enemy::Move() {
	if (moveX) {
		// X�����Ɉړ�
		// ��
		if (direction == 2 || !inLight) {
			if ((PosX - targetX) > 0) {
				nextPosX = PosX - 1;
				if (Map[PosY][nextPosX] != WALL) {
					pos.x -= speed;
					SetDirection(0);
				}
			}
		}
		// �E
		if (direction == 3 || !inLight) {
			if ((PosX - targetX) < 0) {
				nextPosX = PosX + 1;
				if (Map[PosY][nextPosX] != WALL) {
					pos.x += speed;
					SetDirection(1);
				}
			}
		}

		if (std::abs(pos.x - nextPosX * 30.0f) < 0.1f) {
			PosX = nextPosX;
			//Map[PosY][PosX] = 3;
			move = false;
			prevlight = inLight;
			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
			targetX = PosX;
			moveX = false;  // X�����ɂ���ȏ�ړ����Ȃ�
		}
	}

	if (moveY) {
		// Y�����Ɉړ�
		if (direction == 0 || !inLight) {
			if ((PosY - targetY) > 0) {
				nextPosY = PosY - 1;
				if (Map[nextPosY][PosX] != WALL) {
					pos.y += speed;
				}
			}
		}
		if (direction == 1 || !inLight) {
			if ((PosY - targetY) < 0) {
				nextPosY = PosY + 1;
				if (Map[nextPosY][PosX] != WALL) {
					pos.y -= speed;
				}
			}
		}

		if (std::abs(pos.y - (nextPosY * -30.0f)) < 0.1f) {
			PosY = nextPosY;
			//Map[PosY][PosX] = 3;
			move = false;
			prevlight = inLight;
			// �^�[�Q�b�g�̈ʒu�����ݒn�ɐݒ�
			targetY = PosY;
			moveY = false;  // Y�����ɂ���ȏ�ړ����Ȃ�
		}
	}
}

void Enemy::CheckDead(GameScene& game) {
	auto& characterObj = game.GetCharacterObjects(); // �Q�Ƃ��g��

	for (const auto& obj : characterObj) {
		// Player �I�u�W�F�N�g���ǂ������m�F
		Player* player = dynamic_cast<Player*>(obj.get());
		if (player) {
			if (this->CheckCollision(*player)) {
				state = true;
				SetTexture(game.GetTexture_ptr(), L"asset/shake2.png",1,1);
				framecount = 0;
			}
		}
	}
}

void Enemy::Animation() {
	if (framecount % 15 == 0) {
		// 10 �t���[������
		int uvIndex = (framecount / 10) % 4; 

		SetUV(uvIndex, 1);
	}
	// �I��
	if (framecount >= 0) { 
		animationEnd = true;
	}

}


