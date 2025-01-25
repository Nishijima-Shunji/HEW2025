#pragma once
#include "direct3d.h"
//�փb�_�\�����Ύg�����

#define C_UP	(0)
#define C_DOWN	(1)
#define C_RIGHT	(2)
#define C_LEFT	(3)

extern DirectX::XMFLOAT3 Camera_Pos;

//��u
void SetCamera(float x, float y, float z = Camera_Pos.z);
//���킶�퓮��
void MoveCamera(int direction, float speed, float max);
//�Y�[��
void ZoomUp(float speed);
void ZoomOut(float speed);