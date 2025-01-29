//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Object.h"
#include "camera.h"
#include <iostream>
#include <utility>

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------


//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void Object::Init(TextureManager* textureManager, const wchar_t* imgname, int sx, int sy) {
	splitX = sx;
	splitY = sy;

	vertexList[1].u = 1.0f / splitX;
	vertexList[2].v = 1.0f / splitY;
	vertexList[3].u = 1.0f / splitX;
	vertexList[3].v = 1.0f / splitY;

	// ���_�o�b�t�@���쐬����
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// TextureManager��ʂ��ăe�N�X�`�����擾
	m_pTextureView = textureManager->GetTexture(imgname);
	/*if (!m_pTextureView) {
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}*/
}

std::vector<std::vector<int>> Object::Update(std::vector<std::vector<int>> MapDate)
{
	Map = MapDate;

	//std::cout << "���s" << std::endl;

	return Map;
}

void Object::Draw() {
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	// �e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
	g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

	// �萔�o�b�t�@���X�V
	ConstBuffer cb;

	// �v���W�F�N�V�����ϊ��s����쐬
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH / g_Camera.Camera_Pos.z, SCREEN_HEIGHT / g_Camera.Camera_Pos.z, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	// ���[���h�ϊ��s��̍쐬
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x - g_Camera.Camera_Pos.x, pos.y - g_Camera.Camera_Pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	// UV�A�j���[�V�����̍s��쐬�i���E���]�̓K�p�j
	float flipU = (direction == 1) ? -1.0f : 1.0f;  // �E�����Ȃ�U���𔽓]
	float offsetU = (direction == 1) ? 1.0f : 0.0f;  // ���]���ɉE������J�n���邽�߂ɃI�t�Z�b�g��K�p
	cb.matrixTex = DirectX::XMMatrixScaling(flipU, 1.0f, 1.0f);
	cb.matrixTex *= DirectX::XMMatrixTranslation((offsetU + (float)numU) / splitX, (float)numV / splitY, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	// ���_�J���[�̃f�[�^���쐬
	cb.color = color;

	cb.applyBlur = shouldApplyBlur; // shouldApplyBlur ��Object�̏�ԂɊ�Â��t���O

	// �V�F�[�_�[�ɒ萔�o�b�t�@�𑗐M
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);

	// �`�施��
	g_pDeviceContext->Draw(4, 0);
}


void Object::Uninit() {
	SAFE_RELEASE(m_pTextureView);
	SAFE_RELEASE(m_pVertexBuffer);
}

void Object::SetPos(float x, float y, float z) {
	//���W���Z�b�g����
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Object::SetPos(DirectX::XMFLOAT3 _pos) {
	//���W���Z�b�g����
	pos = _pos;
}

void Object::SetSize(float x, float y, float z) {
	//�傫�����Z�b�g����
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetSize(DirectX::XMFLOAT3 _siz) {
	//���W���Z�b�g����
	size = _siz;
}

void Object::SetAngle(float a) {
	//�p�x���Z�b�g����
	angle = a;
}

void Object::SetColor(float r, float g, float b, float a) {
	//�F���Z�b�g����
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

void Object::SetUV(int u, int v) {
	numU = u;
	numV = v;
}

DirectX::XMFLOAT3 Object::GetPos(void) {
	return pos;
}

DirectX::XMFLOAT3 Object::GetSize(void) {
	return size;
}

float Object::GetAngle(void) {
	return angle;
}

DirectX::XMFLOAT4 Object::GetColor(void) {
	return color;
}

std::vector<std::vector<int>> Object::GetMap(std::vector<std::vector<int>> Mapdate)
{
	Map = Mapdate;

	return Mapdate;
}

void Object::SetTexture(TextureManager* textureManager, const wchar_t* imgname) {
	m_pTextureView = textureManager->GetTexture(imgname);
}

// �摜�̌�����ύX����֐��i0:���̂܂܁@1:���E���]�j
void Object::SetDirection(int Direction) {
	// 0��1�łȂ��Ȃ甲����
	if (Direction > 1 || Direction < 0) {
		return;
	}
	direction = Direction;
}

std::vector<std::pair<int, int>> Object::findCoordinate(
	const std::vector<std::vector<int>>& map, int targetValue) {

	std::vector<std::pair<int, int>> coordinates;

	for (size_t y = 0; y < map.size(); ++y) {
		for (size_t x = 0; x < map[y].size(); ++x) {
			if (map[y][x] == targetValue) {
				coordinates.emplace_back(x, y);  // (x, y) �̏��Ŋi�[
			}
		}
	}

	return coordinates;
}

void Object::SetXY(int setX, int setY) {
	PosX = setX;
	PosY = setY;
}


//******************************************************************************
//	End of file.
//******************************************************************************