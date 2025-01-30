#include "Enemy.h"

std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData,GameScene& game)
{
	Map = MapData;

	if (!move) {
		FindLight();
	}

	Move();

	// 到着後に探索を再開
	if (PosX == targetX && PosY == targetY) {
		hasReachedTarget = true;
	}

	// 待機アニメーション
	SetUV(animcount % 8, (animcount / 8) % 2);
	if (framecount % 5 == 0) {
		animcount++;
	}
	framecount++;

	return Map;
}

void Enemy::FindLight() {
	if (move) return;  // 移動中は探索を行わない
	bool foundLight = false;

	if (Map[PosY][PosX] == Luminous) {
		inLight = true;
	}
	else {
		inLight = false;
	}

	// X方向に光を探す
	for (int tempX = PosX - 1; tempX >= 0; tempX--) {
		if (!inLight || direction == 2) {
			// 探索中に壁があればそこでその方向は終了
			if (Map[PosY][tempX] == 1 || Map[PosY][tempX] == 11 || Map[PosY][tempX] == 12) {
				if ((Map[PosY][PosX - 1] == WALL || Map[PosY][PosX - 1] == 11 || Map[PosY][PosX - 1] == 12 || Map[PosY][PosX - 1] == 4) && inLight) {
					direction = 3;
					targetX = tempX;
					moveX = true;
					foundLight = true;
				}
				break;
			}
			if (Map[PosY][tempX] == (20)) {
				targetX = tempX;
				moveX = true;
				foundLight = true;
				break;
			}
		}
		if (inLight && (Map[PosY - 1][PosX != Luminous] && Map[PosY + 1][PosX != Luminous]) && !prevlight) {
			direction = 3;
		}
	}
	for (int tempX = PosX + 1; tempX < 32; tempX++) {
		if (!inLight || direction == 3) {
			// 探索中に壁があればそこでその方向は終了
			if (Map[PosY][tempX] == 1 || Map[PosY][tempX] == 11 || Map[PosY][tempX] == 12) {
				if ((Map[PosY][PosX + 1] == WALL || Map[PosY][PosX + 1] == 11 || Map[PosY][PosX + 1] == 12 || Map[PosY][PosX + 1] == 4) && inLight) {
					direction = 2;
					targetX = tempX;
					moveX = true;
					foundLight = true;
				}
				break;
			}
			if (Map[PosY][tempX] == Luminous) {
				targetX = tempX;
				moveX = true;
				foundLight = true;
				break;
			}
		}
		if (inLight && (Map[PosY - 1][PosX] != Luminous && Map[PosY + 1][PosX] != Luminous) && !prevlight) {
			direction = 3;
		}
	}

	// Y方向に光を探す
	for (int tempY = PosY - 1; tempY >= 0; tempY--) {
		if (!inLight || direction == 0) {
			// 探索中に壁があればそこでその方向は終了
			if (Map[tempY][PosX] == 1 || Map[tempY][PosX] == 11 || Map[tempY][PosX] == 12) {
				if ((Map[PosY - 1][PosX] == WALL || Map[PosY - 1][PosX] == 11 || Map[PosY - 1][PosX] == 12 || Map[PosY - 1][PosX] == 4) && inLight) {
					direction = 1;
					targetY = tempY;
					moveY = true;
					foundLight = true;
				}
				break;
			}
			if (Map[tempY][PosX] == Luminous) {
				targetY = tempY;
				moveY = true;
				foundLight = true;
				break;
			}
		}
		if (inLight && (Map[PosY][PosX - 1] != Luminous && Map[PosY][PosX + 1] != Luminous) && !prevlight) {
			direction = 1;
		}
	}
	for (int tempY = PosY + 1; tempY < 18; tempY++) {
		if (!inLight || direction == 1) {
			// 探索中に壁があればそこでその方向は終了
			if (Map[tempY][PosX] == 1 || Map[tempY][PosX] == 11 || Map[tempY][PosX] == 12) {
				if ((Map[PosY + 1][PosX] == WALL || Map[PosY + 1][PosX] == 11 || Map[PosY + 1][PosX] == 12 || Map[PosY + 1][PosX] == 4) && inLight) {
					direction = 0;
					targetY = tempY;
					moveY = true;
					foundLight = true;
				}
				break;
			}
			if (Map[tempY][PosX] == Luminous) {
				targetY = tempY;
				moveY = true;
				foundLight = true;
				break;
			}
		}
		if (inLight && (Map[PosY][PosX - 1] != Luminous && Map[PosY][PosX + 1] != Luminous) && !prevlight) {
			direction = 1;
		}
	}

	if (!foundLight && hasFoundLightBefore) {
		// 次のマスへの移動処理
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
		// X方向に移動
		if (direction == 2 || !inLight) {
			if ((PosX - targetX) > 0) {
				nextPosX = PosX - 1;
				if (Map[PosY][nextPosX] != WALL) {
					pos.x -= 1.0f;
				}
			}
		}
		if (direction == 3 || !inLight) {
			if ((PosX - targetX) < 0) {
				nextPosX = PosX + 1;
				if (Map[PosY][nextPosX] != WALL) {
					pos.x += 1.0f;
				}
			}
		}

		if (std::abs(pos.x - nextPosX * 30.0f) < 0.1f) {
			// 目的地がプレイヤー(2)ならstateを1にする
			if (Map[PosY][nextPosX] == P_DIVER) {
				state = true;
			}
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
					pos.y += 1.0f;
				}
			}
		}
		if (direction == 1 || !inLight) {
			if ((PosY - targetY) < 0) {
				nextPosY = PosY + 1;
				if (Map[nextPosY][PosX] != WALL) {
					pos.y -= 1.0f;
				}
			}
		}

		if (std::abs(pos.y - (nextPosY * -30.0f)) < 0.1f) {
			// 目的地がプレイヤー(2)ならstateを1にする
			if (Map[nextPosY][PosX] == P_DIVER) {
				state = true;
			}
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


