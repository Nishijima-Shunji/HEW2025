#include "Enemy.h"
#include "GameScene.h"

Enemy::Enemy() {
}

std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	Map = MapData;
	if (!state) {
		if (move) {
			Move();
		}
		else {
			FindLight();
		}

		CheckDead(game);

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
	bool up_check = true, down_check = true, 
		left_check = true, right_check = true;

	targetX = PosX;
	targetY = PosY;

	if (Map[PosY][PosX] == LUMINOUS) {
		inLight = true;
	}
	else {
		inLight = false;
	}

	for (int i = 1;; i++) {
		if (left_check) {
			//�~�܂�ꏊ�̌��m
			if (Map[PosY][PosX - i] == WALL || Map[PosY][PosX - i] == LIGHTUPWALL ||
				Map[PosY][PosX - i] == MAP_END || Map[PosY][PosX - i] == LIGHT_1 ||
				Map[PosY][PosX - i] == GOAL || Map[PosY][PosX - i] == LUMINOUS) {
				//���C�g�̂��Ă镔���ɓ���
				if (Map[PosY][PosX - i] == LUMINOUS && !inLight) {
					targetX = PosX - 1;
					direction = LEFT;
					move = true;
					break;
				}
				//���C�g���ŕǂȂ������ς���
				if (inLight) {
					if(Map[PosY][PosX - 1] == LUMINOUS){
						targetX = PosX - 1;
						direction = LEFT;
						move = true;
						break;
					}
					else {
						direction = RIGHT;
					}
				}
				left_check = false;
			}
		}
		if (up_check) {
			//�~�܂�ꏊ�̌��m
			if (Map[PosY - i][PosX] == WALL || Map[PosY - i][PosX] == LIGHTUPWALL ||
				Map[PosY - i][PosX] == MAP_END || Map[PosY - i][PosX] == LIGHT_1 ||
				Map[PosY - i][PosX] == GOAL || Map[PosY - i][PosX] == LUMINOUS) {
				//���C�g�̂��Ă镔���ɓ���
				if (Map[PosY - i][PosX] == LUMINOUS) {
					targetY = PosY - 1;
					direction = UP;
					move = true;
					break;
				}
				//���C�g���ŕǂȂ������ς���
				if (inLight) {
					if (Map[PosY - 1][PosX] == LUMINOUS) {
						targetY = PosY - 1;
						direction = UP;
						move = true;
						break;
					}
					else {
						direction = DOWN;
					}
				}
				up_check = false;
			}
		}
		if (right_check) {
			//�~�܂�ꏊ�̌��m
			if (Map[PosY][PosX + i] == WALL || Map[PosY][PosX + i] == LIGHTUPWALL ||
				Map[PosY][PosX + i] == MAP_END || Map[PosY][PosX + i] == LIGHT_1 ||
				Map[PosY][PosX + i] == GOAL || Map[PosY][PosX + i] == LUMINOUS) {
				//���C�g�̂��Ă镔���ɓ���
				if (Map[PosY][PosX + i] == LUMINOUS && !inLight) {
					targetX = PosX + 1;
					direction = RIGHT;
					move = true;
					break;
				}
				//���C�g���ŕǂȂ������ς���
				if (inLight) {
					if (Map[PosY][PosX + 1] == LUMINOUS) {
						targetX = PosX + 1;
						direction = RIGHT;
						move = true;
						break;
					}
					else {
						direction = LEFT;
					}
				}
				right_check = false;
			}
		}
		if (down_check) {
			//�~�܂�ꏊ�̌��m
			if (Map[PosY + i][PosX] == WALL || Map[PosY + i][PosX] == LIGHTUPWALL ||
				Map[PosY + i][PosX] == MAP_END || Map[PosY + i][PosX] == LIGHT_1 ||
				Map[PosY + i][PosX] == GOAL || Map[PosY + i][PosX] == LUMINOUS) {
				//���C�g�̂��Ă镔���ɓ���
				if (Map[PosY + i][PosX] == LUMINOUS) {
					targetY = PosY + 1;
					direction = DOWN;
					move = true;
					break;
				}
				//���C�g���ŕǂȂ������ς���
				if (inLight) {
					if (Map[PosY + i][PosX] == LUMINOUS) {
						targetY = PosY - 1;
						direction = DOWN;
						move = true;
						break;
					}
					else {
						direction = UP;
					}
				}
				down_check = false;
			}
		}

		if (up_check == false && down_check == false &&
			left_check == false && right_check == false) {
			break;
		}
	}
}

void Enemy::Move() {
	switch (direction){
	case UP:
		pos.y += speed;
		break;
	case DOWN:
		pos.y -= speed;
		break;
	case RIGHT:
		pos.x += speed;
		SetDirection(1);
		break;
	case LEFT:
		pos.x -= speed;
		SetDirection(0);
		break;
	
	default:
		break;
	}

	if (std::abs(pos.x) - abs(targetX * 30.0f) < 0.1f && 
		std::abs(pos.y) - abs(targetY * 30.0f) < 0.1f) {
		PosX = targetX;
		PosY = targetY;
		move = false;
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