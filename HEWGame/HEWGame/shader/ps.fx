//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

Texture2D g_diffuseTex : register(t1);			// テクスチャ（アルベド）
Texture2D g_normalmapTex : register(t2);		// テクスチャ(ノーマルマップ)

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
	float4 texcol = g_diffuseTex.Sample(g_SamplerLinear, input.Tex);

	// ノーマルマップから法線情報を取得
	float4 N;
	
	N.rgb = g_normalmapTex.Sample(g_SamplerLinear, input.Tex).rgb;
	N.rgb = N.rgb * 2.0f - 1.0f; // (-1から1の範囲に変換)
	N.w = 0.0f;
	N = normalize(N);

	// 光の方向（接ベクトル空間）を取得
	float4 L;
	L.x = input.LightDir.x;
	L.y = input.LightDir.y;
	L.z = input.LightDir.z;
	L.w = 0.0f;

	N = normalize(N);
	L = normalize(L);

	float d = max(0.0, dot(L, N));
	float4 diffuse = d;

	float4 H;
	float4 V = normalize(input.Eye - input.WPos);
	H = normalize(L + V);

	float s = max(0, dot(N, H));
	s = pow(s, 300);
	float4 specular = s;// *specularmaterial;

//    float4 col = specular;
    float4 col = texcol* diffuse + specular;
//	float4 col = N;
	col.a = 1.0f;
	return col;
}