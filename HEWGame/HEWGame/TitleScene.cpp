#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()とsrand()のため
#include <ctime>    // time()のため

TitleScene::TitleScene() {
    TextureManager* textureManager = new TextureManager(g_pDevice);

    // タイトル背景====================
    title_bg = new Object;  // オブジェクト生成
    title_bg->Init(textureManager, L"asset/Bg/sea.png", 8, 4);
    title_bg->SetPos(0.0f, 0.0f, 0.0f);  // 位置を設定
    title_bg->SetSize(1000.0f, 500.0f, 0.0f);  // 大きさを設定
    title_bg->SetAngle(0.0f);  // 角度を設定
    title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // 色を設定

    // タイトル名=======================
    title_name = new Object;
    title_name->Init(textureManager, L"asset/Title_test.png", 8, 4);
    title_name->SetPos(0.0f, 0.0f, 1.0f);  // 位置を設定
    title_name->SetSize(300.0f, 300.0f, 0.0f);  // 大きさを設定
    title_name->SetAngle(0.0f);  // 角度を設定
    title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // 色を設定

    // タイトルオブジェクト=============
    InitTitleObjects(10);  // ランダムな位置に10個のオブジェクトを初期化
}

TitleScene::~TitleScene() {
    delete title_bg;
    delete title_name;
    for (auto obj : title_Ob) {
        delete obj;
    }
}

void TitleScene::InitTitleObjects(int count) {
    TextureManager* textureManager = new TextureManager(g_pDevice);
    srand(static_cast<unsigned>(time(0)));  // ランダム数生成のためのシード

    for (int i = 0; i < count; ++i) {
        Object* obj = new Object;
        obj->Init(textureManager, L"asset/Bg/konbu.png", 8, 4);
        float x = static_cast<float>((rand() % 1000)-500);  // ランダムなx位置
        float y = static_cast<float>((rand() % 500)-400);   // ランダムなy位置
        // yの値が小さいほど大きくする
        float sizeFactor_Bg = 1.0f + (25.0f - y) / 25.0f;  // yが小さいほどsizeFactorが大きくなる
        float width_konbu = 10.0f * sizeFactor_Bg;//昆布の幅
        float height_konbu = 10.0f * sizeFactor_Bg;//高さ
        obj->SetPos(x, y, 1.0f);  // 位置を設定
        obj->SetSize(width_konbu, height_konbu, 0.0f);  // 大きさを設定
        obj->SetAngle(0.0f);  // 角度を設定
        obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // 色を設定
        title_Ob.push_back(obj);
    }
}

// シーンのアップデート
void TitleScene::Update() {
    input.Update();  // キー入力の判定
    if (input.GetKeyTrigger(VK_2)) {
        SceneManager::ChangeScene(SceneManager::SELECT);  // シーンをGAMEへ移行
    }
}

// 各シーンの描画
void TitleScene::Draw() {
    title_bg->Draw();
    title_name->Draw();
    for (auto obj : title_Ob) {
        obj->Draw();
    }
}