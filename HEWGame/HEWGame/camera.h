#pragma once
#include "direct3d.h"

class Camera {
private:
	Camera();
	~Camera();
	//�J�����̃|�W�V����
	DirectX::XMFLOAT3	Camera_Speed = { 0.0f, 0.0f, 0.0f };
	int count = 0, move_count = 0;

public:
	static Camera& GetInstance() {
		static Camera instance;
		return instance;
	}

	DirectX::XMFLOAT3 Camera_Pos = { 0.0f, 0.0f, 1.0f };

	void Update();

	//��u
	void SetCamera(float x, float y, float z = 1.0f);
	//���킶�퓮��
	void MoveCamera(float new_x, float new_y, float new_z, int count);
};

#define g_Camera Camera::GetInstance()