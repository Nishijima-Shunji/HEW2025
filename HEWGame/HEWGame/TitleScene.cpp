#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()とsrand()のため
#include <ctime>    // time()のため

TitleScene::TitleScene() {
	textureManager = new TextureManager(g_pDevice);

	// ロゴ表示
	logo = std::make_unique<Object>();
	logo->Init(textureManager, L"asset/logo.png");
	logo->SetPos(0.0f, 0.0f, 0.0f);
	logo->SetSize(800.0f, 800.0f, 0.0f);
	logo->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	state = 0;
	// タイトルオブジェクト=============
	//InitTitleObjects(10);  // ランダムな位置に10個のオブジェクトを初期化
}

TitleScene::~TitleScene() {
	delete textureManager;
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
		float x = static_cast<float>((rand() % 1000) - 500);  // ランダムなx位置
		float y = static_cast<float>((rand() % 500) - 400);   // ランダムなy位置
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
	// ロゴ表示中に読み込み
	if (state == 0) {
		// 仮
		//playSE();

		// タイトル背景====================
		title_bg = new Object;
		title_bg->Init(textureManager, L"asset/title/title 2_000.png");
		title_bg->SetPos(0.0f, 0.0f, 0.0f);         // 位置を設定
		title_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // 大きさを設定

		// タイトル名=======================
		title_name = new Object;
		title_name->Init(textureManager, L"asset/title.png");
		title_name->SetPos(0.0f, 200.0f, 1.0f);       // 位置を設定
		title_name->SetSize(993.0f, 315.0f, 0.0f);  // 大きさを設定

		//// ボタン設置
		//for (int i = 0; i < 3; i++) {
		//    button[i] = std::make_unique<Object>();
		//    button[i]->Init(textureManager,L"asset/button");
		//    button[i]->SetPos((i * 100.0f) - 300.0f, 0.0f, 0.0f);
		//    button[i]->SetSize(100.0f,100.0f,0.0f);
		//}


		if (framecount == 1) {
			// 事前に読み込み
			for (int i = 0; i < 300; i++) {
				if (i % 5 == 0) {
					std::wstring texturePath = L"asset/title/title 2_";
					std::wstring tmp = L"000" + std::to_wstring(i);	// 3桁に調整   
					tmp = tmp.substr(tmp.size() - 3);  // 最後の3桁のみを使用
					texturePath += tmp;
					texturePath += L".png";
					title_bg->SetTexture(textureManager, texturePath.c_str());
				}
			}
		}

		logo->SetColor(1.0f, 1.0f, 1.0f, logo->GetColor().w - 0.01f);
		if (logo->GetColor().w <= 0) {
			state = 1;
		}
	}
	else if (state == 1) {
		input.Update();  // キー入力の判定
		if (input.GetKeyRelease(VK_RETURN)){
			SceneManager::ChangeScene(SceneManager::SELECT);  // シーンをGAMEへ移行
		}

		// 一応アニメーションなるけど重すぎる
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
				title_bg->SetTexture(textureManager, texturePath.c_str());
			}
		}
	}
	framecount++;
}

// 各シーンの描画
void TitleScene::Draw() {
	if (state == 0) {
		logo->Draw();
	}
	else if (state == 1) {
		title_bg->Draw();
		title_name->Draw();
		for (auto obj : title_Ob) {
			obj->Draw();
		}
	}
}