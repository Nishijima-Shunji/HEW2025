#include "StageSelectScene.h"
#include "Game.h"

// 前の一応残しとく　あとで消す
 
//StageSelectScene::StageSelectScene() {
//	textureManager = new TextureManager(g_pDevice);
//
//	select_bg = std::make_unique<Object>();
//	select_bg->Init(textureManager, L"asset/stage_select2/stage_select 2_000.png", 8, 4);
//	select_bg->SetPos(0.0f, 0.0f, 0.0f);			//位置を設定
//	select_bg->SetSize(1920.0f, 1080.0f, 0.0f);		//大きさを設定
//	select_bg->SetAngle(0.0f);						//角度を設定
//	select_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//色を設定
//	// 事前に読み込み
//	for (int i = 0; i < 300; i++) {
//		if (i % 5 == 0) {
//			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
//			std::wstring pathindex = L"000" + std::to_wstring(i);	// 3桁に調整   
//			pathindex = pathindex.substr(pathindex.size() - 3);  // 最後の3桁のみを使用
//			texturePath += pathindex;
//			texturePath += L".png";
//			select_bg->SetTexture(textureManager, texturePath.c_str());
//		}
//	}
//	// ステージのアイコン画像を生成
//	for (int i = 0; i < 8; i++) {
//		// 生成
//		stageicon.emplace_back(std::make_unique<Object>());
//		// インデックス毎のパス指定
//		std::wstring texturePath = L"asset/stage_icon/";
//		texturePath += std::to_wstring(i + 1);
//		texturePath += L".png";
//		stageicon[i]->Init(textureManager, texturePath.c_str());
//		stageicon[i]->SetPos(i * 800.0f + 0.0f, -170.0f, 0.0f);
//		stageicon[i]->SetSize(400.0f, 400.0f, 0.0f);
//	}
//	sensuikan = std::make_unique<Object>();
//	sensuikan->Init(textureManager, L"asset/sensuikan.png", 1, 1);
//	sensuikan->SetPos(0.0f, -400.0f, 0.0f);			//位置を設定
//	sensuikan->SetSize(310.25f, 250.0f, 0.0f);		//大きさを設定
//}
//
//StageSelectScene::~StageSelectScene() {
//	delete textureManager;
//}
//
//void StageSelectScene::Update() {
//	input.Update();
//
//	if (nowStage != nextStage) {
//		if (nowStage < nextStage) {
//			for (auto& obj : stageicon) {
//				DirectX::XMFLOAT3 pos = obj->GetPos();
//				pos.x -= 8.0f;
//				obj->SetPos(pos.x, pos.y, pos.z);
//			}
//		}
//		else
//		{
//			for (auto& obj : stageicon) {
//				DirectX::XMFLOAT3 pos = obj->GetPos();
//				pos.x += 8.0f;
//				obj->SetPos(pos.x, pos.y, pos.z);
//			}
//		}
//	}
//
//	if (stageicon[nextStage - 1]->GetPos().x == 0.0f) {
//		nowStage = nextStage;
//	}
//
//	// ステージ移動
//	if (input.GetKeyTrigger(VK_LEFT) && nowStage > 1) {
//		nextStage -= 1;
//	}
//	if (input.GetKeyTrigger(VK_RIGHT) && nowStage < 8) {
//		nextStage += 1;
//	}
//	if (input.GetKeyTrigger(VK_RETURN) && nowStage == nextStage) {
//		// 現在位置の番号ステージでゲームシーン読み込み
//		SceneManager::ChangeScene(SceneManager::GAME, nowStage);
//	}
//	// 一応アニメーションなるけど重すぎる
//	if (framecount % 1 == 0) {
//		int textureIndex = (framecount / 1) % 300;  // 0 から 299 の範囲にリマップ
//		// 仮で5フレーム毎のアニメーションに
//		if (textureIndex % 5 == 0) {
//			// 現在のアニメーションに対応するパスに組み合わせる
//			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
//			std::wstring pathindex = L"000" + std::to_wstring(textureIndex);	// 3桁に調整   
//			pathindex = pathindex.substr(pathindex.size() - 3);  // 最後の3桁のみを使用
//			texturePath += pathindex;
//			texturePath += L".png";
//			select_bg->SetTexture(textureManager, texturePath.c_str());
//		}
//	}
//	framecount++;
//}
//
//void StageSelectScene::Draw() {
//	select_bg->Draw();
//	for (auto& obj : stageicon) {
//		obj->Draw();
//	}
//	sensuikan->Draw();
//}

StageSelectScene::StageSelectScene() {
	textureManager = new TextureManager(g_pDevice);

	select_bg = std::make_unique<Object>();
	select_bg->Init(textureManager, L"asset/stage_select2/stage_select 2_000.png", 1, 1);
	select_bg->SetPos(0.0f, 0.0f, 0.0f);			//位置を設定
	select_bg->SetSize(1920.0f, 1080.0f, 0.0f);		//大きさを設定
	select_bg->SetAngle(0.0f);						//角度を設定
	select_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//色を設定

	load_bg = std::make_unique<Object>();
	load_bg->Init(textureManager, L"asset/loadbg.png", 1, 1);
	load_bg->SetPos(0.0f, 0.0f, 0.0f);			//位置を設定
	load_bg->SetSize(0.0f, 0.0f, 0.0f);			//大きさを設定

	// 事前に読み込み
	for (int i = 0; i < 300; i++) {
		if (i % 5 == 0) {
			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
			std::wstring pathindex = L"000" + std::to_wstring(i);	// 3桁に調整   
			pathindex = pathindex.substr(pathindex.size() - 3);  // 最後の3桁のみを使用
			texturePath += pathindex;
			texturePath += L".png";
			select_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
	// ステージのアイコン画像を生成
	for (int i = 0; i < 4; i++) {
		// 生成
		stageicon.emplace_back(std::make_unique<Object>());
		// インデックス毎のパス指定
		std::wstring texturePath = L"asset/stage_icon/";
		texturePath += std::to_wstring(i + 1);
		texturePath += L".png";

		stageicon[i]->Init(textureManager, texturePath.c_str());
		stageicon[i]->SetPos(i * 475.0f - 700.0f, -230.0f, 0.0f);
		stageicon[i]->SetSize(230.0f, 230.0f, 0.0f);
	}
	sensuikan = std::make_unique<Object>();
	sensuikan->Init(textureManager, L"asset/sensuikan.png", 1, 1);
	sensuikan->SetPos(-700.0f, -400.0f, 0.0f);		//位置を設定
	sensuikan->SetSize(265.25f, 200.0f, 0.0f);		//大きさを設定

	loadstate = 0;
}

StageSelectScene::~StageSelectScene() {
	delete textureManager;
}

void StageSelectScene::Update() {
	input.Update();

	// 今いる位置が目的地じゃないなら移動
	if (nowStage != nextStage) {
		move = true;
	}
	else {
		move = false;
	}
	if (move) {
		if (nowStage < nextStage) {
			DirectX::XMFLOAT3 pos = sensuikan->GetPos();
			pos.x += 10.0f;
			sensuikan->SetPos(pos.x, pos.y, pos.z);
		}
		else
		{
			DirectX::XMFLOAT3 pos = sensuikan->GetPos();
			pos.x -= 10.0f;
			sensuikan->SetPos(pos.x, pos.y, pos.z);
		}
	}
	if (nextStage < 5) {
		// 目的地と今の位置がだいたい同じなら停止
		if (abs((stageicon[nextStage - 1]->GetPos().x - sensuikan->GetPos().x)) < 10.0f) {
			nowStage = nextStage;
		}
	}
	else if (nextStage > 4) {
		// 目的地と今の位置がだいたい同じなら停止
		if (abs((stageicon[nextStage - 5]->GetPos().x - sensuikan->GetPos().x)) < 10.0f) {
			nowStage = nextStage;
		}
	}

	// 画面切り替え
	// 右端か左端に行ったとき
	if ((sensuikan->GetPos().x > 1000.0f && nextStage == 5 && loadstate == 0)
		|| (sensuikan->GetPos().x < -1000.0f && nextStage == 4 && loadstate == 0)) {
		loadstate = 1;
	}

	// 切り替え中
	if (loadstate == 1) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x += 60.0f;
		size.y += 60.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x > 2500.0f) {
			loadstate = 3;
		}
	}
	// 画面戻す
	if (loadstate == 2) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x -= 60.0f;
		size.y -= 60.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x < -10.0f) {
			loadstate = 0;
		}
	}
	if (loadstate == 3) {
		int count = 0;
		for (auto& obj : stageicon) {
			std::wstring texturePath = L"asset/stage_icon/";
			if (nextStage == 5) {
				texturePath += std::to_wstring(count + 5);
			}
			else if (nextStage == 4) {
				texturePath += std::to_wstring(count + 1);
			}
			texturePath += L".png";
			obj->SetTexture(textureManager, texturePath.c_str());
			count++;
		}
		if (nextStage == 5) {
			sensuikan->SetPos(-1200.0f, -400.0f, 0.0f);
		}
		else if (nextStage == 4) {
			sensuikan->SetPos(1200.0f, -400.0f, 0.0f);
		}
		loadstate = 2;
	}

	// 切り替え中
	if (loadstate == 1) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x += 80.0f;
		size.y += 80.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x > 2500.0f) {
			loadstate = 3;
		}
	}
	if (loadstate == 3) {
		int count = 0;
		for (auto& obj : stageicon) {
			std::wstring texturePath = L"asset/stage_icon/";
			texturePath += std::to_wstring(count + 5);
			texturePath += L".png";
			obj->SetTexture(textureManager, texturePath.c_str());
			count++;
		}
		sensuikan->SetPos(-1000.0f, -400.0f, 0.0f);
		loadstate = 4;
	}
	if (loadstate == 4) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x -= 80.0f;
		size.y -= 80.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x < -10.0f) {
			loadstate = 0;
		}
	}

	// 移動
	if (!move) {
		// ステージ移動
		if (input.GetKeyTrigger(VK_LEFT) && nowStage > 1) {
			nextStage -= 1;
		}
		if (input.GetKeyTrigger(VK_RIGHT) && nowStage < 8) {
			nextStage += 1;
		}
		// 決定
		if (input.GetKeyTrigger(VK_RETURN) && nowStage == nextStage) {
			// 現在位置の番号ステージでゲームシーン読み込み
			SceneManager::ChangeScene(SceneManager::GAME, nowStage);
		}
	}


	// 一応アニメーションなるけど重すぎる
	if (framecount % 1 == 0) {
		int textureIndex = (framecount / 1) % 300;  // 0 から 299 の範囲にリマップ
		// 仮で5フレーム毎のアニメーションに
		if (textureIndex % 5 == 0) {
			// 現在のアニメーションに対応するパスに組み合わせる
			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
			std::wstring pathindex = L"000" + std::to_wstring(textureIndex);	// 3桁に調整   
			pathindex = pathindex.substr(pathindex.size() - 3);  // 最後の3桁のみを使用
			texturePath += pathindex;
			texturePath += L".png";
			select_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
	framecount++;
}

void StageSelectScene::Draw() {
	select_bg->Draw();
	for (auto& obj : stageicon) {
		obj->Draw();
	}
	sensuikan->Draw();

	// 一番前にするから最後
	if (loadstate > 0) {
		load_bg->Draw();
	}
}