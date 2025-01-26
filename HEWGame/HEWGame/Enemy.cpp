#include "Enemy.h"

std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData)
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

	lightX = false;
	lightY = false;
	bool foundLight = false;

	// X方向に光を探す
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

	// Y方向に光を探す
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
			// 目的地がプレイヤー(2)ならstateを1にする
			if (Map[PosY][nextPosX] == P_DIVER) {
				state = true;
			}
			PosX = nextPosX;
			Map[PosY][PosX] = 3;
			move = false;

			// ターゲットの位置を現在地に設定
			targetX = PosX;
			moveX = false;  // X方向にこれ以上移動しない
		}
	}

	if (moveY) {
		// Y方向に移動
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
			// 目的地がプレイヤー(2)ならstateを1にする
			if (Map[nextPosY][PosX] == P_DIVER) {
				state = true;
			}
 			PosY = nextPosY;
			Map[PosY][PosX] = 3;
			move = false;

			// ターゲットの位置を現在地に設定
			targetY = PosY;
			moveY = false;  // Y方向にこれ以上移動しない
		}
	}
}

//void Enemy::Move() {
//	if (moveX) {
//		// X方向に移動
//		if ((PosX - targetX) > 0) {
//			nextPosX = PosX - 1;
//			if (Map[PosY][nextPosX] != WALL) {
//				pos.x -= 1.0f;
//			}
//		}
//		else {
//			nextPosX = PosX + 1;
//			if (Map[PosY][nextPosX] != WALL) {
//				pos.x += 1.0f;
//			}
//		}
//
//		if (std::abs(pos.x - nextPosX * 30.0f) < 0.1f) {
//			// 現在の位置を記憶しておく（最初の移動時のみ）
//			if (!hasStoredPrevTile) {
//				prevObj = Map[PosY][PosX];  // 現在のタイル内容を保存
//				hasStoredPrevTile = true;
//			}
//
//			// 先に新しい位置の内容を記憶
//			int nextTile = Map[PosY][nextPosX];
//
//			// 目的地がプレイヤー(2)ならstateを1にする
//			if (nextTile == P_DIVER) {
//				state = true;
//			}
//
//			// 現在の位置を元のタイルに戻す
//			Map[PosY][PosX] = prevObj;
//
//			// 敵の位置を更新
//			PosX = nextPosX;
//
//			// 新しい位置の内容を次回のために保存
//			prevObj = nextTile;
//
//			// 新しい位置に敵を配置
//			Map[PosY][PosX] = 3;
//
//			move = false;
//			targetX = PosX;
//			moveX = false;  // X方向にこれ以上移動しない
//		}
//	}
//
//	if (moveY) {
//		// Y方向に移動
//		if ((PosY - targetY) > 0) {
//			nextPosY = PosY - 1;
//			if (Map[nextPosY][PosX] != WALL) {
//				pos.y += 1.0f;
//			}
//		}
//		else {
//			nextPosY = PosY + 1;
//			if (Map[nextPosY][PosX] != WALL) {
//				pos.y -= 1.0f;
//			}
//		}
//
//		// 目的地に到着したら処理
//		if (std::abs(pos.y - (nextPosY * -30.0f)) < 0.1f) {
//			// 現在の位置を記憶しておく
//			if (!hasStoredPrevTile) {
//				prevObj = Map[PosY][PosX];  // 現在のタイル内容を保存
//				hasStoredPrevTile = true;
//			}
//
//			// 敵の移動処理
//			Map[PosY][PosX] = prevObj;   // 元の位置に記憶していた内容を戻す
//
//			// 目的地がプレイヤー(2)ならstateを1にする
//			if (Map[nextPosY][PosX] == P_DIVER) {
//				state = true;
//			}
//
//			PosY = nextPosY;
//			prevObj = Map[nextPosY][PosX];  // 新しい位置の内容を記憶
//			Map[PosY][PosX] = 3;  // 新しい位置に敵を配置
//
//			move = false;
//			targetY = PosY;
//			moveY = false;  // Y方向にこれ以上移動しない
//		}
//	}
//}


