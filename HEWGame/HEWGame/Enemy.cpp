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

	int exitCheck = NOTHING;

	for (int i = 1;; i++) {
		for (int check_dir = 0; check_dir < 4; check_dir++) {
			switch ((direction + check_dir) % 4) {
			case E_UP:
				if (up_check) {
					exitCheck = CheckAllDirection(PosY - i, PosX, E_UP);
					if (exitCheck == STOP_CHECK)	up_check = false;
				}
				break;

			case E_RIGHT:
				if (right_check) {
					exitCheck = CheckAllDirection(PosY, PosX + i, E_RIGHT);
					if (exitCheck == STOP_CHECK)	right_check = false;
				}
				break;
				
			case E_DOWN:
				if (down_check) {
					exitCheck = CheckAllDirection(PosY + i, PosX, E_DOWN);
					if (exitCheck == STOP_CHECK)	down_check = false;
				}
				break;

			case E_LEFT:
				if (left_check) {
					exitCheck = CheckAllDirection(PosY, PosX - i, E_LEFT);
					if (exitCheck == STOP_CHECK)	left_check = false;
				}
				break;
			}
			if (exitCheck == STOP_MOVE) break;
		}
		if (exitCheck == STOP_MOVE) break;

		if (up_check == false && down_check == false &&
			left_check == false && right_check == false) break;
	}
}

int Enemy::CheckAllDirection(int pos_y, int pos_x, int dire)
{					
	//�~�܂�ꏊ�̌��m
	if (Map[pos_y][pos_x] == WALL || Map[pos_y][pos_x] == LIGHTUPWALL ||
		Map[pos_y][pos_x] == MAP_END || Map[pos_y][pos_x] == LIGHT_1 || Map[pos_y][pos_x] == LIGHT_2 ||
		Map[pos_y][pos_x] == GOAL || Map[pos_y][pos_x] == LUMINOUS) {
		//���C�g���ŕǂȂ������ς���
		if (inLight) {
			if (Map[pos_y][pos_x] == LUMINOUS) {
				DirectionCase(dire);
				direction = dire;
				move = true;
				return STOP_MOVE;
			}
			else {
				direction = (dire + 2) % 4;
				return STOP_MOVE;
			}
		}
		//���C�g�̂��Ă镔���ɓ���
		if (Map[pos_y][pos_x] == LUMINOUS) {
			DirectionCase(dire);
			direction = dire;
			move = true;
			return STOP_MOVE;
		}
		return STOP_CHECK;
	}
	return NOTHING;
}
void Enemy::DirectionCase(int dire) 
{
	switch (dire)
	{
	case E_UP:
		targetY = PosY - 1;
		break;
	case E_RIGHT:
		targetX = PosX + 1;
		break;
	case E_DOWN:
		targetY = PosY + 1;
		break;
	case E_LEFT:
		targetX = PosX - 1;
		break;
	}
}

void Enemy::Move() {
	switch (direction){
	case E_UP:
		pos.y += speed;
		break;
	case E_RIGHT:
		pos.x += speed;
		SetDirection(1);
		break;
	case E_DOWN:
		pos.y -= speed;
		break;
	case E_LEFT:
		pos.x -= speed;
		SetDirection(0);
		break;
	
	default:
		break;
	}

	if (std::abs(std::abs(pos.x) - abs(targetX * 30.0f)) < 0.1f &&
		std::abs(std::abs(pos.y) - abs(targetY * 30.0f)) < 0.1f) {
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