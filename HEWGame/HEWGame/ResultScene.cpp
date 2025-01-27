#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int setscore, int setMscore, int settime) : Score(setscore), Mscore(setMscore), timescore(settime) {
	textureManager = new TextureManager(g_pDevice);

	result_bg = std::make_unique<Object>();
	result_bg->Init(textureManager, L"asset/title/title 2_000.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);         // 位置を設定
	result_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // 大きさを設定

	board = std::make_unique<Object>();
	board->Init(textureManager, L"asset/UI/result.png");
	board->SetPos(400.0f, 0.0f, 0.0f);         // 位置を設定
	board->SetSize(1000.0f, 1000.0f, 0.0f);	// 大きさを設定

	sensuikan = std::make_unique<Object>();
	sensuikan->Init(textureManager, L"asset/UI/sensuikan.png");
	sensuikan->SetPos(-400.0f, 0.0f, 0.0f);         // 位置を設定
	sensuikan->SetSize(800.0f, 800.0f, 0.0f);  // 大きさを設定

	button = std::make_unique<Object>();
	button->Init(textureManager, L"asset/UI/Abutton.png");
	button->SetPos(800.0f, -450.0f, 0.0f);         // 位置を設定
	button->SetSize(100.0f, 100.0f, 0.0f);  // 大きさを設定

	for (int i = 0; i < 3; i++) {
		mendako.emplace_back(std::make_unique<Object>());
		mendako[i]->Init(textureManager, L"asset/UI/mendako2.png");
		mendako[i]->SetPos((i * 185.0f) + 215.0f, -98.5f, 0.0f);         // 位置を設定
		mendako[i]->SetSize(175.0f, 175.0f, 0.0f);  // 大きさを設定
	}
	mendako[1]->SetPos(402.0f, -98.5f, 0.0f);


	for (int i = 0; i < 5; i++) {
		// UIの生成
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/UI/num.png", 10, 1);	// 仮の画像を使用
		scoreNum.back()->SetPos((i * 60.0f) + 380.0f, -250.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);

		timeNum.emplace_back(std::make_unique<Object>());
		timeNum.back()->Init(textureManager, L"asset/UI/num.png", 10, 1);	// 仮の画像を使用
		timeNum.back()->SetPos((i * 60.0f) + 380.0f, 60.0f, 0.0f);
		timeNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		timeNum.back()->SetUV(0, 0);
	}
	// 事前に読み込み
	for (int i = 0; i < 300; i++) {
		if (i % 5 == 0) {
			std::wstring texturePath = L"asset/title/title 2_";
			std::wstring tmp = L"000" + std::to_wstring(i);	// 3桁に調整   
			tmp = tmp.substr(tmp.size() - 3);  // 最後の3桁のみを使用
			texturePath += tmp;
			texturePath += L".png";
			result_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
	Mscore = 2;
	Score = 53492;
	tempScore = Score;
}

ResultScene::~ResultScene() {
	delete textureManager;
}

void ResultScene::Update() {
	input.Update();

	if (state == 0) {
		// 数字を高速で回す
		for (int i = 0; i < 5; i++) {
			scoreNum[i]->SetUV(rand() % 10, 0);
		}
		if (framecount == 100) {
			state = 1;          // スコア確定へ移行
			revealIndex = 0;    // 桁の表示開始位置
			scoreFixCounter = 0; // スコア確定用の新しいカウンター
		}
	}
	else if (state == 1) {
		// 桁を右から順に1つずつ固定
		if ( scoreFixCounter > 75 + (Mscore * 50)) {
			if (scoreFixCounter % 8 == 0 && revealIndex < static_cast<int>(scoreNum.size())) {
				int digit = tempScore % 10;  // 右端の桁を取得
				tempScore /= 10;             // 次の桁へ
				scoreNum[scoreNum.size() - 1 - revealIndex]->SetUV(digit, 0);
				revealIndex++;
			}
		}

		// 確定した桁は固定し、未確定の桁は引き続きランダム表示
		for (int i = 0; i < static_cast<int>(scoreNum.size()) - revealIndex; i++) {
			scoreNum[i]->SetUV(rand() % 10, 0);
		}

		DirectX::XMFLOAT3 offsetSize = { 2000.0f, 2000.0f, 0.0f };
		if (mendakoSet == 0) {
			mendako[0]->SetSize(offsetSize.x - animtime * 30, offsetSize.y - animtime * 30, offsetSize.z);
			if (mendako[0]->GetSize().x < 175.0f) {
				mendako[0]->SetSize(175.0f, 175.0f, 0.0f);
				mendakoSet = 1;
				animtime = 0;
			}
		}
		else if (mendakoSet == 1) {
			mendako[1]->SetSize(offsetSize.x - animtime * 30, offsetSize.y - animtime * 30, offsetSize.z);
			if (mendako[1]->GetSize().x < 175.0f) {
				mendako[1]->SetSize(175.0f, 175.0f, 0.0f);
				mendakoSet = 2;
				animtime = 0;
			}
		}
		else if (mendakoSet == 2) {
			mendako[2]->SetSize(offsetSize.x - animtime * 30, offsetSize.y - animtime * 30, offsetSize.z);
			if (mendako[2]->GetSize().x < 175.0f) {
				mendako[2]->SetSize(175.0f, 175.0f, 0.0f);
				mendakoSet = 3;
				animtime = 0;
			}
		}
		animtime++;

		/*if (mendakoSet < mendako.size()) {
			mendako[mendakoSet]->SetSize(offsetSize.x - animtime, offsetSize.y - animtime, offsetSize.z);
			if (mendako[mendakoSet]->GetSize().x < 175.0f) {
				mendakoSet++;
				animtime = 0;
			}
		}*/

		// 全桁確定後、次の状態へ
		if (revealIndex >= static_cast<int>(scoreNum.size()) && mendakoSet == 3) {
			state = 2;
		}

		scoreFixCounter++;  // 確定処理のカウントを進める
	}
	else if (state == 2) {
		if (input.GetKeyTrigger(VK_SPACE) || input.GetButtonTrigger(VK_A)) {
			state = 3;
		}
	}
	else if (state == 3) {
		float speed = 80.0f;
		board->SetPos(board->GetPos().x + speed, board->GetPos().y, board->GetPos().z);
		button->SetPos(button->GetPos().x + speed, button->GetPos().y, button->GetPos().z);
		for (int i = 0; i < mendako.size(); i++) {
			mendako[i]->SetPos(mendako[i]->GetPos().x + speed, mendako[i]->GetPos().y, mendako[i]->GetPos().z);
		}
		for (int i = 0; i < scoreNum.size(); i++) {
			timeNum[i]->SetPos(timeNum[i]->GetPos().x + speed, timeNum[i]->GetPos().y, timeNum[i]->GetPos().z);
			scoreNum[i]->SetPos(scoreNum[i]->GetPos().x + speed, scoreNum[i]->GetPos().y, scoreNum[i]->GetPos().z);
		}
		// 現在位置を取得
		DirectX::XMFLOAT3 tmpPos = sensuikan->GetPos();

		// 加速度を適用して速度を増加
		velocityY += acceleration;

		// 速度を適用して位置を更新
		sensuikan->SetPos(tmpPos.x, tmpPos.y + velocityY, tmpPos.z);

		// 上限チェック
		if (sensuikan->GetPos().y > 1000.0f) {
			SceneManager::ChangeScene(SceneManager::SELECT);
			velocityY = 0.0f;  // シーン変更時に速度をリセット
		}
	}


	// アニメーション
	BgAnimation();
	if (state < 3) {
		SensuikanAnimation();
	}


	framecount++;
	framecount = (framecount + 1) % 3600;
}

void ResultScene::Draw() {
	result_bg->Draw();
	board->Draw();
	sensuikan->Draw();
	button->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
	for (auto& obj : timeNum) {
		obj->Draw();
	}
	for (int i = 0; i < Mscore; i++) {
		if (mendakoSet >= i && state > 0) {
			mendako[i]->Draw();
		}
	}
}

void ResultScene::BgAnimation() {
	// アニメーション
	if (framecount % 1 == 0) {
		int textureIndex = (framecount / 1) % 300;  // 0 から 299 の範囲にリマップ
		// 仮で5フレーム毎1アニメーションに
		if (textureIndex % 5 == 0) {
			// 現在のアニメーションに対応するパスに組み合わせる
			std::wstring texturePath = L"asset/title/title 2_";
			std::wstring tmp = L"000" + std::to_wstring(textureIndex);	// 3桁に調整   
			tmp = tmp.substr(tmp.size() - 3);  // 最後の3桁のみを使用
			texturePath += tmp;
			texturePath += L".png";
			result_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
}

void ResultScene::SensuikanAnimation() {
	// 初期位置
	DirectX::XMFLOAT3 initialPos(-400.0f, 0.0f, 0.0f);

	// X軸とY軸にサイン波で揺れを加える
	float offsetX = amplitude * sin(framecount * frequency + noise);
	float offsetY = amplitude * 0.5f * sin(framecount * frequency * 1.2f);

	// 位置を設定
	sensuikan->SetPos(initialPos.x + offsetX, initialPos.y + offsetY, initialPos.z);
}