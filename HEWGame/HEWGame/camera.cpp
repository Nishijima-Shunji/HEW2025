#include "camera.h"

//�J�����̃|�W�V����
DirectX::XMFLOAT3 Camera_Pos = { 0.0f, 0.0f, 1.0f };

//�ʒu�Œ�
void SetCamera(float x, float y, float z)
{
	Camera_Pos.x = x;
	Camera_Pos.y = y;
	Camera_Pos.z = z;
}

//������
void MoveCamera(int direction, float speed, float max)
{
	switch (direction)
	{
	case C_UP:
		if (Camera_Pos.y < max) {
			Camera_Pos.y += speed;
		}
		else {
			Camera_Pos.y = max;
		}
		break;

	case C_DOWN:
		if (Camera_Pos.y > max) {
			Camera_Pos.y -= speed;
		}
		else {
			Camera_Pos.y = max;
		}
		break;

	case C_RIGHT:
		if (Camera_Pos.x < max) {
			Camera_Pos.x += speed;
		}
		else {
			Camera_Pos.x = max;
		}
		break;

	case C_LEFT:
		if (Camera_Pos.x > max) {
			Camera_Pos.x -= speed;
		}
		else {
			Camera_Pos.x = max;
		}
		break;
	}
}

//�Y�[���֘A
void ZoomUp(float speed)
{
	Camera_Pos.z += speed / 100.0f;
	if (Camera_Pos.z < 0.1) {
		Camera_Pos.z = 0.1;
	}
}

void ZoomOut(float speed)
{
	Camera_Pos.z -= speed / 100.0f;
}