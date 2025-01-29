//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------
//cbuffer ConstantBuffer : register(b0) {
//    float2 textureSize;  // �e�N�X�`���T�C�Y�i�s�N�Z���P�ʁj
//};
//
//// �s�N�Z���̏��̍\���́i�󂯎��p�j
//struct PS_IN
//{
//    // float4�^ �� float�^���S�̍\����
//    float4 pos : SV_POSITION; // �s�N�Z���̉�ʏ�̍��W
//    float4 col : COLOR0;      // �F�̏��
//    float2 tex : TEXCOORD0;   // �s�N�Z����UV���W
//};
//
//// �O���[�o���ϐ��̐錾
//// ��C���ꑤ����f�[�^��n���ꂽ���ɃZ�b�g�����ϐ�
//Texture2D myTexture : register(t0);    // �e�N�X�`��
//SamplerState mySampler : register(s0); // �T���v���[
//
//// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
//float4 ps_main(PS_IN input) : SV_Target
//{
//    // �e�N�X�`������Y����UV�ʒu�̃s�N�Z���F���擾
//    float4 color = myTexture.Sample(mySampler, input.tex);
//
//    // ���͂̐F�Ɗ|���Z
//    color *= input.col;
//
//    // �ڂ₯���ʂ�K�p���邩�ǂ����̃t���O���`�F�b�N
//    if (applyBlur)
//    {
//        // ���S����̋������v�Z
//        float2 center = float2(0.5, 0.5);    // ���S�ʒu�iUV���W�n�ł�0.5, 0.5�����S�j
//        float distanceFromCenter = length(input.tex - center);
//
//        // �����Ɋ�Â��ăA���t�@�l�𒲐��i�ڂ₯���ʁj
//        float alpha = saturate(1.0 - distanceFromCenter * 2.0);  // �����������قǃA���t�@�l���������Ȃ�
//
//        // �A���t�@�l��K�p
//        color.a *= alpha;
//    }
//
//    return color;
//}

// �萔�o�b�t�@�̒�`
cbuffer ConstantBuffer : register(b0) {
    float2 textureSize;      // �e�N�X�`���T�C�Y�i�s�N�Z���P�ʁj
    bool applyBlur;          // �ڂ₯���ʂ�K�p���邩�ǂ���
    float fadeRange;         // �ڂ₯�͈�
    float fadeStrength;      // �t�F�[�h�̋���
    float padding[2];        // �p�f�B���O�i16�o�C�g���E�̂��߁j
};

// �s�N�Z���V�F�[�_�[�̓��͍\����
struct PS_IN {
    float4 pos : SV_POSITION;  // �s�N�Z���̉�ʏ�̍��W
    float4 col : COLOR0;       // ���_�J���[
    float2 tex : TEXCOORD;     // �s�N�Z����UV���W
};

// �e�N�X�`���ƃT���v���[�̐錾
Texture2D myTexture : register(t0);  // �e�N�X�`��
SamplerState mySampler : register(s0);  // �T���v���[

// �s�N�Z���V�F�[�_�[�̃��C���֐�
float4 ps_main(PS_IN input) : SV_Target
{
    // �e�N�X�`������F���擾
    float4 color = myTexture.Sample(mySampler, input.tex);

    // applyBlur �� true �̏ꍇ�ɂڂ₯���ʂ�K�p
    if (applyBlur)
    {
        // �ڂ₯�͈͂��l�����ăt�F�[�h���ʂ��v�Z
        float2 center = float2(0.5, 0.5);
        float distanceFromCenter = length(input.tex - center);
        float alpha = saturate(1.0 - distanceFromCenter * fadeRange);  // �ڂ₯�͈͂Ɋ�Â��A���t�@�l

        // �t�F�[�h�̋�����K�p
        alpha = alpha * fadeStrength;

        // �A���t�@�l��F�ɓK�p���Č��ʂ�Ԃ�
        color.a *= alpha;
    }

    // �F�ƒ��_�J���[���|�����킹�čŏI�I�ȐF���v�Z
    color *= input.col;

    return color;  // �ŏI�I�ȃJ���[��Ԃ�
}
