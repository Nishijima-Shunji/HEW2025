//--------------------------------------------------------------------------------------
// vs.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.fx"

//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[
//--------------------------------------------------------------------------------------
VS_OUTPUT main(
	float4 Pos		: POSITION,
	float4 Normal	: NORMAL,
	float2 Tex		: TEXCOORD,
	float4 Tangent	: TANGENT,
	float4 Binormal : BINORMAL	)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4  P;      // ���[���h���W
	float4	B;		// �]�@���x�N�g��
	float4	T;		// �ڃx�N�g��
	float4	N;		// �@���x�N�g��
	float4	L;		// ���̕����x�N�g��

	P = Pos;
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Tex = Tex;

	// �]�@�������[���h�ϊ�
	Binormal.w = 0;
	B = Binormal;

	// �ڃx�N�g�������[���h�ϊ�
	Tangent.w = 0;
	T = Tangent;

	// �@�������[���h�ϊ�
	Normal.w = 0;
	N = Normal;

	// ���K��
	B = normalize(B);
	T = normalize(T);
	N = normalize(N);

	// ���̕����𐳋K��
	L = normalize(float4(invLightDirection.xyz, 0));
	L.w = 0;

	// ���̕�����ڃx�N�g����Ԃɕϊ����邽�߂�
	// �ڃx�N�g����ԍs��
	//    TTT0
	//    BBB0
	//    NNN0
	//    0001
	//     �̋t�s������߂�
	//       (�]�u�łn�j�j
	//    TBN0
	//    TBN0
	//    TBN0
	//    0001

	// ���̕�����ڃx�N�g����Ԃɕϊ�
	output.LightDir.x = dot(L, T);
	output.LightDir.y = dot(L, B);
	output.LightDir.z = dot(L, N);

	// ���_�ʒu�i���[�J�����W�n�j��ڃx�N�g����Ԃɕϊ�
	output.Eye.x = dot(invEyePos, T);
	output.Eye.y = dot(invEyePos, B);
	output.Eye.z = dot(invEyePos, N);

	// ���[�J�����W��ڃx�N�g����Ԃɕϊ�
	output.WPos.x = dot(P, T);
	output.WPos.y = dot(P, B);
	output.WPos.z = dot(P, N);

	return output;
}