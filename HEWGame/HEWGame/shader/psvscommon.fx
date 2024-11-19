Texture2D g_Tex : register(t0);				// �e�N�X�`��
SamplerState g_SamplerLinear : register(s0);	// �T���v���[

//--------------------------------------------------------------------------------------
// �R���X�^���g�o�b�t�@
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
	float4 LightDirection;			// ���̕���
	float4 EyePos;					// ���_�ʒu
	float4 invLightDirection;		// ���̕����i�t�s����|�������̕����j
	float4 invEyePos;				// ���_�ʒu�i�t�s����|�������_�̈ʒu�j
}

cbuffer ConstantBufferBoneMatrix : register(b5)
{
	matrix BoneMatrix[400];
}

//--------------------------------------------------------------------------------------
// �\���̒�`
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;		// �X�N���[�����W
	float4 Color	: COLOR0;			// �f�B�t���[�Y
	float4 Color2	: COLOR1;			// �X�y�L����
	float2 Tex		: TEXCOORD;			// �e�N�X�`�����W
	float4 WPos		: TEXCOORD1;		// ���_���W(���[���h���W)
	float4 Normal	: TEXCOORD2;		// �@���x�N�g��(���[�J�����W)
	float4 LPos		: TEXCOORD3;		// ���_���W(���[�J�����W)
	float4 LightDir : TEXCOORD4;		// ���̕���(�ڃx�N�g�����)
	float4 Eye      : TEXCOORD5;		// �J�����ʒu(�ڃx�N�g�����)
};