#include "O2.h"

void O2::Update() {
    switch (state) {
    case 0:
        // 初期状態
        break;
    case 1:
        break;
    case 2:
        // 初回の弾き処理
        if (!init) {
            velocityY = 20.0f;  // 上向きに弾く初速度
            velocityX = (rand() % 200 - 100) * 0.08f;  // -1.0 ~ 1.0 のランダムなX方向速度
            init = true;  // 一度だけ初期化
        }
        angle += 20.0f;
        velocityY -= gravity;  // 重力適用
        pos.y += velocityY;    // 落下
        pos.x += velocityX;    // 左右の動き
        break;
    }
}
