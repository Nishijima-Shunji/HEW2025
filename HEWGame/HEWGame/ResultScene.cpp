#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int score) : score(score) {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result_test.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);			//位置を設定
	result_bg->SetSize(300.0f, 300.0f, 0.0f);		//大きさを設定
	result_bg->SetAngle(0.0f);						//角度を設定
	result_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//色を設定

	for (int i = 0; i < 5; i++) {
		// UIの生成
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);	// 仮の画像を使用
		scoreNum.back()->SetPos((i * 60.0f) - 125.0f, 0.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}

	// スコア表示
	int tempScore = score;
	for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
		int digit = tempScore % 10;  // 右端の桁を取得
		tempScore /= 10;            // スコアを10で割って次の桁へ進む

		// UVを桁の値に基づいて設定
		scoreNum[i]->SetUV(digit, 0);
		//scorest.emplace_back(digit);
	}
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
	input.Update();

	if (state == 0) {
		// スコアを決まるまで適当に動かす
		for (int i = 0; i < 5; i++) {
			scoreNum[i]->SetUV(rand() % 10, rand() % 10);
		}
		if (count == 300) {
			state = 1;
		}
		count++;
	}
	else if (state == 1) {

	}

	if (input.GetKeyTrigger(VK_1)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw() {
	result_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}