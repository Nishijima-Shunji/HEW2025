#include "Enemy.h"


std::vector<std::vector<int>> Enemy::Update(std::vector<std::vector<int>> MapData)
{
	Map = MapData;

	// マップの位置データからEnemyの位置を取得
	//FindEnemyPos();

	// 移動先を探索
	if (!move) {
		moveX = false;
		moveY = false;
		FindLight();

		// 縦移動と横移動の距離が短い方へ移動
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
	// Enemyの座標を取得
	auto Enemypos = findCoordinate(Map, 3);
	for (const auto& coord : Enemypos) {
		PosX = coord.first;
		PosY = coord.second;
	}
}

void Enemy::FindLight() {
	static bool foundLight = false; // ライトを一度見つけたら記憶する
	lightX = false;
	lightY = false;

	if (targetX != PosX) {
		for (int tempX = PosX; tempX > 0; tempX--) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
				foundLight = true; // ライト発見を記録
			}
		}
		for (int tempX = PosX; tempX < 32; tempX++) {
			if (Map[PosY][tempX] == 20) {
				targetX = tempX;
				lightX = true;
				moveX = true;
				foundLight = true; // ライト発見を記録
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

	// ライトが見つからなくても、以前のターゲットに向かう
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

		// 目標地点に到達したら停止
		if (pos.x == nextPosX * 30.0f) {
			PosX = nextPosX;
			Map[PosY][PosX + 1] = 0;  // 元の位置をクリア
			Map[PosY][PosX] = 3;       // 新しい位置を更新
			move = false;
			movingToTarget = false;    // 目標に到達したので移動フラグをリセット
		}
	}
	else if (moveY) {
		// Y方向の移動処理（同様に適用）
	}

	std::cout << moveX << std::endl;
}
