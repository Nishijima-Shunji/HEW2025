//--------------------------------------------------------------------------------------
// ピクセルシェーダー
//--------------------------------------------------------------------------------------
//cbuffer ConstantBuffer : register(b0) {
//    float2 textureSize;  // テクスチャサイズ（ピクセル単位）
//};
//
//// ピクセルの情報の構造体（受け取り用）
//struct PS_IN
//{
//    // float4型 → float型が４つの構造体
//    float4 pos : SV_POSITION; // ピクセルの画面上の座標
//    float4 col : COLOR0;      // 色の情報
//    float2 tex : TEXCOORD0;   // ピクセルのUV座標
//};
//
//// グローバル変数の宣言
//// ※C言語側からデータを渡された時にセットされる変数
//Texture2D myTexture : register(t0);    // テクスチャ
//SamplerState mySampler : register(s0); // サンプラー
//
//// ピクセルシェーダーのエントリポイント
//float4 ps_main(PS_IN input) : SV_Target
//{
//    // テクスチャから該当のUV位置のピクセル色を取得
//    float4 color = myTexture.Sample(mySampler, input.tex);
//
//    // 入力の色と掛け算
//    color *= input.col;
//
//    // ぼやけ効果を適用するかどうかのフラグをチェック
//    if (applyBlur)
//    {
//        // 中心からの距離を計算
//        float2 center = float2(0.5, 0.5);    // 中心位置（UV座標系では0.5, 0.5が中心）
//        float distanceFromCenter = length(input.tex - center);
//
//        // 距離に基づいてアルファ値を調整（ぼやけ効果）
//        float alpha = saturate(1.0 - distanceFromCenter * 2.0);  // 距離が遠いほどアルファ値が小さくなる
//
//        // アルファ値を適用
//        color.a *= alpha;
//    }
//
//    return color;
//}

// 定数バッファの定義
cbuffer ConstantBuffer : register(b0) {
    float2 textureSize;      // テクスチャサイズ（ピクセル単位）
    bool applyBlur;          // ぼやけ効果を適用するかどうか
    float fadeRange;         // ぼやけ範囲
    float fadeStrength;      // フェードの強さ
    float padding[2];        // パディング（16バイト境界のため）
};

// ピクセルシェーダーの入力構造体
struct PS_IN {
    float4 pos : SV_POSITION;  // ピクセルの画面上の座標
    float4 col : COLOR0;       // 頂点カラー
    float2 tex : TEXCOORD;     // ピクセルのUV座標
};

// テクスチャとサンプラーの宣言
Texture2D myTexture : register(t0);  // テクスチャ
SamplerState mySampler : register(s0);  // サンプラー

// ピクセルシェーダーのメイン関数
float4 ps_main(PS_IN input) : SV_Target
{
    // テクスチャから色を取得
    float4 color = myTexture.Sample(mySampler, input.tex);

    // applyBlur が true の場合にぼやけ効果を適用
    if (applyBlur)
    {
        // ぼやけ範囲を考慮してフェード効果を計算
        float2 center = float2(0.5, 0.5);
        float distanceFromCenter = length(input.tex - center);
        float alpha = saturate(1.0 - distanceFromCenter * fadeRange);  // ぼやけ範囲に基づくアルファ値

        // フェードの強さを適用
        alpha = alpha * fadeStrength;

        // アルファ値を色に適用して結果を返す
        color.a *= alpha;
    }

    // 色と頂点カラーを掛け合わせて最終的な色を計算
    color *= input.col;

    return color;  // 最終的なカラーを返す
}
