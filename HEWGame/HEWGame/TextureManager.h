#pragma once

#include <d3d11_1.h>
#include <string>
#include <map>

class TextureManager {
public:
    TextureManager(ID3D11Device* device);
    ~TextureManager();

    // テクスチャを取得する（キャッシュに存在すればそれを返す）
    ID3D11ShaderResourceView* GetTexture(const wchar_t* imgname);

private:
    ID3D11Device* m_device;
    std::map<std::wstring, ID3D11ShaderResourceView*> textureCache;

    // テクスチャをキャッシュに追加する内部関数
    HRESULT LoadTextureFromFile(const wchar_t* imgname, ID3D11ShaderResourceView** textureView);

    // キャッシュされたテクスチャを解放する
    void ReleaseAllTextures();
};
