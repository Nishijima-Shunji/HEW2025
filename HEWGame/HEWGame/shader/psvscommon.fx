Texture2D g_Tex : register(t0);				// テクスチャ
SamplerState g_SamplerLinear : register(s0);	// サンプラー

//--------------------------------------------------------------------------------------
// コンスタントバッファ
//--------------------------------------------------------------------------------------
cbuffer ConstantBufferWorld : register(b0)
{
	matrix World;
}

cbuffer ConstantBufferView : register(b1)
{
	matrix View;
}

cbuffer ConstantBufferProjection : register(b2)
{
	matrix Projection;
}

cbuffer ConstantBufferMaterial : register(b3)
{
	float4	ambientMaterial;
	float4	diffuseMaterial;
	float4	specularMaterial;
}

cbuffer ConstantBufferLight : register(b4)
{
	float4 LightDirection;			// 光の方向
	float4 EyePos;					// 視点位置
	float4 invLightDirection;		// 光の方向（逆行列を掛けた光の方向）
	float4 invEyePos;				// 視点位置（逆行列を掛けた視点の位置）
}

cbuffer ConstantBufferBoneMatrix : register(b5)
{
	matrix BoneMatrix[400];
}

//--------------------------------------------------------------------------------------
// 構造体定義
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;		// スクリーン座標
	float4 Color	: COLOR0;			// ディフューズ
	float4 Color2	: COLOR1;			// スペキュラ
	float2 Tex		: TEXCOORD;			// テクスチャ座標
	float4 WPos		: TEXCOORD1;		// 頂点座標(ワールド座標)
	float4 Normal	: TEXCOORD2;		// 法線ベクトル(ローカル座標)
	float4 LPos		: TEXCOORD3;		// 頂点座標(ローカル座標)
	float4 LightDir : TEXCOORD4;		// 光の方向(接ベクトル空間)
	float4 Eye      : TEXCOORD5;		// カメラ位置(接ベクトル空間)
};