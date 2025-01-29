#pragma once

#include "direct3d.h"
#include "WICTextureLoader.h"
#include "TextureManager.h"
#include <iostream>
#include <vector>

//ステージオブジェクト一覧
#define NOTHING  (-1)	//無
#define SPACE    (0)	//空間
#define WALL     (1)	//壁
#define P_DIVER  (2)	//プレイヤー
#define E_SHARK  (3)	//エネミー
#define GOAL     (4)	//ゴール
#define MENDAKO  (5)	//メンダコ
#define MIRROR_U (6)	//鏡鯛（右上がり）
#define MIRROR_D (7)	//鏡鯛（左下がり）
#define TRAP     (8)	//トラップ
#define STREAM_R (9)	//海流（右）
#define STREAM_L (10)	//海流（左）
#define MAP_END  (11)	//マップ端（ライトの移動場所）
#define LIGHT_1  (12)	//ライト（レベル：1)
#define LIGHT_2  (13)	//ライト（レベル：2）
#define LIGHT_3  (14)	//ライト（レベル：3）
#define MOB_1    (15)	//オニキンメ
#define MOB_2    (16)	//アンコウ
#define D_LIGHT  (19)	//デバッグ用ライト
#define Luminous (20)	//発光マス

class Object
{
private:
protected:
	Vertex vertexList[4] =
	{
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

	// 他のメンバー変数
	bool shouldApplyBlur;  // ぼやけ効果を適用するかどうかを決めるフラグ

	//テクスチャが縦横に何分割されているか
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

	//右上から何個目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;

	virtual void Init(TextureManager* textureManager, const wchar_t* imgname, int sx = 1, int sy = 1);
	virtual std::vector<std::vector<int>> Update(std::vector<std::vector<int>>);
	virtual void Draw();
	virtual void Uninit();
   
	void SetPos(float x, float y, float z);	//座標をセット
	void SetPos(DirectX::XMFLOAT3 _pos);
	void SetSize(float x, float y, float z);//大きさをセット
	void SetSize(DirectX::XMFLOAT3 _siz);
	void SetAngle(float a);	//角度をセット
	void SetColor(float r, float g, float b, float a);
	void SetUV(int u, int v);
	void SetDirection(int);
	void SetXY(int, int);
	void SetShouldApplyBlur(bool set) { shouldApplyBlur = set; };

	std::vector<std::vector<int>> GetMap(std::vector<std::vector<int>>);

	void SetTexture(TextureManager* textureManager, const wchar_t* imgname);  // テクスチャ設定


};

