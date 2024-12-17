//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "TextureManager.h"
#include "WICTextureLoader.h" // CreateWICTextureFromFile を使うために必要

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// グローバル変数
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

TextureManager::TextureManager(ID3D11Device* device)
    : m_device(device)
{
    // コンストラクタ
}

TextureManager::~TextureManager() {
    // デストラクタでキャッシュ内の全テクスチャを解放
    ReleaseAllTextures();
}

ID3D11ShaderResourceView* TextureManager::GetTexture(const wchar_t* imgname) {
    // ファイルパスを絶対パスに変換
    wchar_t fullPath[MAX_PATH];
    GetFullPathName(imgname, MAX_PATH, fullPath, NULL);

    std::wstring imgPath = fullPath;

    // キャッシュを確認
    auto it = textureCache.find(imgPath);
    if (it != textureCache.end()) {
        // キャッシュに存在する場合、参照カウントを増やして返す
        it->second->AddRef();
        //printf("存在するテクスチャ\n");
        return it->second;
    }

    // 新しくテクスチャを読み込む
    ID3D11ShaderResourceView* textureView = nullptr;
    HRESULT hr = LoadTextureFromFile(fullPath, &textureView);
    if (FAILED(hr)) {
        MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
        return nullptr;
    }

    // キャッシュに追加
    textureCache[imgPath] = textureView;
    printf("新しく登録\n");
    return textureView;
}

HRESULT TextureManager::LoadTextureFromFile(const wchar_t* imgname, ID3D11ShaderResourceView** textureView) {
    // テクスチャをファイルから読み込む
    return DirectX::CreateWICTextureFromFile(m_device, imgname, NULL, textureView);
}

void TextureManager::ReleaseAllTextures() {
    // キャッシュ内の全テクスチャを解放
    for (auto& pair : textureCache) {
        if (pair.second) {
            pair.second->Release();
        }
    }
    textureCache.clear();
}
//******************************************************************************
//	End of file.
//******************************************************************************