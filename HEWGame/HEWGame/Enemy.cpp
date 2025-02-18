#include "Enemy.h"
#include "GameScene.h"

//あほ

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
		// 到着後に探索を再開
		if (PosX == targetX && PosY == targetY) {
			hasReachedTarget = true;
		}

		// 待機アニメーション
		SetUV(animcount % 8, (animcount / 8) % 2);
		if (framecount % 5 == 0) {
			animcount++;
		}
	}
	else {
		if (!animationEnd) {
			// サメの噛みつきアニメーション
			Animation();
		}
	}
	framecount++;

	return Map;
}

void Enemy::FindLight() {
	if (move) return;  // 移動中は探索を行わない
	bool foundLight = false;

	if (Map[PosY][PosX] == LUMINOUS) {
		inLight = true;
	}
	else {
		inLight = false;
	}

	// X方向に光を探す
	for (int tempX = PosX - 1; tempX > 0; tempX--) {
		if (!inLight || direction == LEFT) {
			// 探索中に壁があればそこでその方向は終了
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
			// 光が見つかったら目的地設定
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
			// 探索中に壁があればそこでその方向は終了
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

	// Y方向に光を探す
	for (int tempY = PosY - 1; tempY > 0; tempY--) {
		if (!inLight || direction == UP) {
			// 探索中に壁があればそこでその方向は終了
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
			// 探索中に壁があればそこでその方向は終了
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
		// 次のマスへの移動処理
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
		// X方向に移動
		// 左
		if (direction == 2 || !inLight) {
			if ((PosX - targetX) > 0) {
				nextPosX = PosX - 1;
				if (Map[PosY][nextPosX] != WALL) {
					pos.x -= speed;
					SetDirection(0);
				}
			}
		}
		// 右
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
			// ターゲットの位置を現在地に設定
			targetX = PosX;
			moveX = false;  // X方向にこれ以上移動しない
		}
	}

	if (moveY) {
		// Y方向に移動
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
			// ターゲットの位置を現在地に設定
			targetY = PosY;
			moveY = false;  // Y方向にこれ以上移動しない
		}
	}
}

void Enemy::CheckDead(GameScene& game) {
	auto& characterObj = game.GetCharacterObjects(); // 参照を使う

	for (const auto& obj : characterObj) {
		// Player オブジェクトかどうかを確認
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
		// 10 フレームごと
		int uvIndex = (framecount / 10) % 4; 

		SetUV(uvIndex, 1);
	}
	// 終了
	if (framecount >= 0) { 
		animationEnd = true;
	}

}


