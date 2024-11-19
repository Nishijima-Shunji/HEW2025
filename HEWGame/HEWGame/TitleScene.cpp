#include "TitleScene.h"
#include "Game.h"

TitleScene::TitleScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	title_bg = new Object;  // オブジェクト生成
	title_bg->Init(textureManager, L"asset/Title_test.png", 8, 4);
	title_bg->SetPos(0.0f, 0.0f, 0.0f);	//位置を設定
	title_bg->SetSize(300.0f, 300.0f, 0.0f);	//大きさを設定
	title_bg->SetAngle(0.0f);	//角度を設定
	title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//色を設定
}
TitleScene::~TitleScene() {
	delete title_bg;
}

//シーンのアップデート
void TitleScene::Update() {
	input.Update();	//キー入力の判定
	if (input.GetKeyTrigger(VK_2)) {
		SceneManager::ChangeScene(SceneManager::GAME);	//シーンをGAMEへ移行
	}
}

//各シーンの描画
void TitleScene::Draw() {
	title_bg->Draw();
}