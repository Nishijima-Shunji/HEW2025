#include "Camera.h"
#include <cmath>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (count < move_count) {
		Camera_Pos.x += Camera_Speed.x;
		Camera_Pos.y += Camera_Speed.y;
		Camera_Pos.z += Camera_Speed.z;
	}

	count++;
}

void Camera::SetCamera(float x, float y, float z)
{
	Camera_Pos.x = x;
	Camera_Pos.y = y;
	Camera_Pos.z = z;
}

void Camera::MoveCamera(float x, float y, float z, int _count)
{
	count = 0;
	move_count = _count;

	float de;

	if (x > Camera_Pos.x) {
		Camera_Speed.x = abs(x - Camera_Pos.x) / _count;
	}
	else {
		Camera_Speed.x = -abs(x - Camera_Pos.x) / _count;
	}

	if (y > Camera_Pos.y) {
		Camera_Speed.y = abs(y - Camera_Pos.y) / _count;
	}
	else {
		Camera_Speed.y = -abs(y - Camera_Pos.y) / _count;
	}

	if (z > Camera_Pos.z) {
		Camera_Speed.z = abs(z - Camera_Pos.z) / _count;
	}
	else {
		Camera_Speed.z = -abs(z - Camera_Pos.z) / _count;
	}
}