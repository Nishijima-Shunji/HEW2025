#pragma once
#include "direct3d.h"
//へッダ―入れれば使えるよ

#define C_UP	(0)
#define C_DOWN	(1)
#define C_RIGHT	(2)
#define C_LEFT	(3)

extern DirectX::XMFLOAT3 Camera_Pos;

//一瞬
void SetCamera(float x, float y, float z = Camera_Pos.z);
//じわじわ動く
void MoveCamera(int direction, float speed, float max);
//ズーム
void ZoomUp(float speed);
void ZoomOut(float speed);