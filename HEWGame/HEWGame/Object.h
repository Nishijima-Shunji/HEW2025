#pragma once

#include "direct3d.h"
#include "WICTextureLoader.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>

class Object
{
private:
protected:
	Vertex vertexList[4] =
	{
		//=============TRIANGLE================
		//{ -0.5f,  0.5f, 0.5f },  // ０番目の頂点座標　{ x, y, z }
		//{  0.5f, -0.5f, 0.5f },  // １番目の頂点座標
		//{ -0.5f, -0.5f, 0.5f },  // ２番目の頂点座標

		//{  0.6f,  0.6f, 0.5f },  // ３番目の頂点座標
		//{  0.6f, -0.4f, 0.5f },  // ４番目の頂点座標
		//{ -0.4f,  0.6f, 0.5f },  // ５番目の頂点座標

		//=============TRIANGLESTRIP===============
		//	x      y     z     r     g     b     a     u     v
		{-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},  // ０番目の頂点座標　{ x, y, z }
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},  // １番目の頂点座標
		{-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},  // ２番目の頂点座標
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},  // ３番目の頂点座標
	};

	//座標
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	//大きさ
	DirectX::XMFLOAT3 size = { 100.0f, 100.0f, 0.0f };
	//角度
	float angle = 0.0f;
	//色
	DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 頂点バッファ
	//ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	ID3D11ShaderResourceView* m_pTextureView = nullptr;
	

	//テクスチャが縦横に何分割されているか
	int splitX = 1;
	int splitY = 1;

protected:

	std::vector<std::vector<int>> Map = {};

public:

	DirectX::XMFLOAT3 GetPos(void);
	DirectX::XMFLOAT3 GetSize(void);
	float GetAngle(void);
	DirectX::XMFLOAT4 GetColor(void);

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	virtual void Init(TextureManager* textureManager, const wchar_t* imgname, int sx = 1, int sy = 1);
	virtual std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	virtual void Draw();
	virtual void Uninit();
   
	void SetPos(float x, float y, float z);	//座標をセット
	void SetSize(float x, float y, float z);//大きさをセット
	void SetAngle(float a);	//角度をセット
	void SetColor(float r, float g, float b, float a);

	std::vector<std::vector<int>> GetMap(std::vector<std::vector<int>>);


};

