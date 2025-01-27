#include "O2.h"

void O2::Update() {
    switch (state) {
    case 0:
        // �������
        break;
    case 1:
        break;
    case 2:
        // ����̒e������
        if (!init) {
            velocityY = 20.0f;  // ������ɒe�������x
            velocityX = (rand() % 200 - 100) * 0.08f;  // -1.0 ~ 1.0 �̃����_����X�������x
            init = true;  // ��x����������
        }
        angle += 20.0f;
        velocityY -= gravity;  // �d�͓K�p
        pos.y += velocityY;    // ����
        pos.x += velocityX;    // ���E�̓���
        break;
    }
}
