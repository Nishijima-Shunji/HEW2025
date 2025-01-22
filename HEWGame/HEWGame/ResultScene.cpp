#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int score) : Score(score) {
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
		scoreNum.back()->SetPos((i * 60.0f) + 120.0f, 0.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
    input.Update();

    if (state == 0) {
        // 数字を高速で回す
        for (int i = 0; i < 5; i++) {
            scoreNum[i]->SetUV(rand() % 10,0);
        }
        if (count == 100) {
            state = 1;          // スコア確定へ移行
            revealIndex = 0;    // 桁の表示開始位置
            count = 0;          // カウントリセット
        }
    }
    else if (state == 1) {
        // 桁を右から順に1つずつ固定
        if (count % 8 == 0 && revealIndex < static_cast<int>(scoreNum.size())) {
            int digit = tempScore % 10;  // 右端の桁を取得
            tempScore /= 10;             // 次の桁へ
            scoreNum[scoreNum.size() - 1 - revealIndex]->SetUV(digit, 0);
            revealIndex++;
        }

        // 確定した桁は固定し、未確定の桁は引き続きランダム表示
        for (int i = 0; i < static_cast<int>(scoreNum.size()) - revealIndex; i++) {
            scoreNum[i]->SetUV(rand() % 10,0);
        }

        // 全桁確定後、次の状態へ
        if (revealIndex >= static_cast<int>(scoreNum.size())) {
            state = 2;
        }
    }

    if (input.GetKeyTrigger(VK_1)) {
        SceneManager::ChangeScene(SceneManager::TITLE);
    }
    count++;
}

void ResultScene::Draw() {
	result_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}