//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
// 頂点シェーダー
//--------------------------------------------------------------------------------------
VS_OUTPUT main(
	float4 Pos		: POSITION,
	float4 Normal	: NORMAL,
	float2 Tex		: TEXCOORD,
	float4 Tangent	: TANGENT,
	float4 Binormal : BINORMAL	)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4  P;      // ワールド座標
	float4	B;		// 従法線ベクトル
	float4	T;		// 接ベクトル
	float4	N;		// 法線ベクトル
	float4	L;		// 光の方向ベクトル

	P = Pos;
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Tex = Tex;

	// 従法線をワールド変換
	Binormal.w = 0;
	B = Binormal;

	// 接ベクトルをワールド変換
	Tangent.w = 0;
	T = Tangent;

	// 法線をワールド変換
	Normal.w = 0;
	N = Normal;

	// 正規化
	B = normalize(B);
	T = normalize(T);
	N = normalize(N);

	// 光の方向を正規化
	L = normalize(float4(invLightDirection.xyz, 0));
	L.w = 0;

	// 光の方向を接ベクトル空間に変換するために
	// 接ベクトル空間行列
	//    TTT0
	//    BBB0
	//    NNN0
	//    0001
	//     の逆行列を求める
	//       (転置でＯＫ）
	//    TBN0
	//    TBN0
	//    TBN0
	//    0001

	// 光の方向を接ベクトル空間に変換
	output.LightDir.x = dot(L, T);
	output.LightDir.y = dot(L, B);
	output.LightDir.z = dot(L, N);

	// 視点位置（ローカル座標系）を接ベクトル空間に変換
	output.Eye.x = dot(invEyePos, T);
	output.Eye.y = dot(invEyePos, B);
	output.Eye.z = dot(invEyePos, N);

	// ローカル座標を接ベクトル空間に変換
	output.WPos.x = dot(P, T);
	output.WPos.y = dot(P, B);
	output.WPos.z = dot(P, N);

	return output;
}