#pragma once

#include "direct3d.h"
#include "WICTextureLoader.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>

//�X�e�[�W�I�u�W�F�N�g�ꗗ
#define NOTHING  (-1)	//��
#define SPACE    (0)	//���
#define WALL     (1)	//��
#define P_DIVER  (2)	//�v���C���[
#define E_SHARK  (3)	//�G�l�~�[
#define GOAL     (4)	//�S�[��
#define MENDAKO  (5)	//�����_�R
#define MIRROR_U (6)	//����i�E�オ��j
#define MIRROR_D (7)	//����i��������j
#define TRAP     (8)	//�g���b�v
#define STREAM_R (9)	//�C���i�E�j
#define STREAM_L (10)	//�C���i���j
#define MAP_END  (11)	//�}�b�v�[�i���C�g�̈ړ��ꏊ�j
#define LIGHT_1  (12)	//���C�g�i���x���F1)
#define LIGHT_2  (13)	//���C�g�i���x���F2�j
#define LIGHT_3  (14)	//���C�g�i���x���F3�j
#define MOB_1    (15)	//�I�j�L����
#define MOB_2    (16)	//�A���R�E
#define D_LIGHT  (19)	//�f�o�b�O�p���C�g
#define Luminous (20)	//�����}�X

class Object
{
private:
protected:
	Vertex vertexList[4] =
	{
		//=============TRIANGLESTRIP===============
		//	x      y     z     r     g     b     a     u     v
		{-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},  // �O�Ԗڂ̒��_���W�@{ x, y, z }
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},  // �P�Ԗڂ̒��_���W
		{-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},  // �Q�Ԗڂ̒��_���W
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},  // �R�Ԗڂ̒��_���W
	};

	//���W
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	//�傫��
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//�p�x
	float angle = 0.0f;
	//�F
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// ���_�o�b�t�@
	//ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11ShaderResourceView* m_pTextureView = nullptr;

	// ���̃����o�[�ϐ�
	bool shouldApplyBlur;  // �ڂ₯���ʂ�K�p���邩�ǂ��������߂�t���O

	//�e�N�X�`�����c���ɉ���������Ă��邩
	int splitX = 1;
	int splitY = 1;

	int direction = 0;

	int PosX;
	int PosY;

protected:

	std::vector<std::vector<int>> Map = {};
	std::vector<std::pair<int, int>> findCoordinate(const std::vector<std::vector<int>>& map, int targetValue);

public:

	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//�E�ォ�牽�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;

	virtual void Init(TextureManager* textureManager, const wchar_t* imgname, int sx = 1, int sy = 1);
	virtual std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	virtual void Draw();
	virtual void Uninit();
   
	void SetPos(float x, float y, float z);	//���W���Z�b�g
	void SetPos(DirectX::XMFLOAT3 _pos);
	void SetSize(float x, float y, float z);//�傫�����Z�b�g
	void SetSize(DirectX::XMFLOAT3 _siz);
	void SetAngle(float a);	//�p�x���Z�b�g
	void SetColor(float r, float g, float b, float a);
	void SetUV(int u, int v);
	void SetDirection(int);
	void SetXY(int, int);
	void SetShouldApplyBlur(bool set) { shouldApplyBlur = set; };

	std::vector<std::vector<int>> GetMap(std::vector<std::vector<int>>);

	void SetTexture(TextureManager* textureManager, const wchar_t* imgname);  // �e�N�X�`���ݒ�


};

