﻿#include "GameScene.h"
#include "Game.h"
#include <algorithm>
#include "camera.h"

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ankou.h"
#include "Kagamidai.h"
#include "Kairyu.h"
#include "Mendako.h"
#include "Onikinme.h"
#include "Trap.h"
#include "File.h"

// ステージの経過時間計測用変数
std::chrono::high_resolution_clock::time_point start;

// textureMappingの初期化
	//マップからオブジェクトを生成する際に参照するキー
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},		//無
	{1, L"asset/Wall.png"},			//壁
	{2, L"asset/survivor3.png"},	//プレイヤー
	{3, L"asset/shake1.png"},		//敵
	{4, L"asset/S_Goal.png"},		//ゴール
	{5, L"asset/mendako.png"},		//メンダコ
	{6, L"asset/mirror_fish.png"},	//鏡鯛
	{7, L"asset/mirror_fish.png"},	//鏡鯛
	{8, L"asset/S_trap.png"},		//トラップ
	{9, L"asset/S_Kairyu.png"},		//海流
	{10, L"asset/S_Kairyu.png"},	//海流
	{11, L"asset/Wall2.png"},		//マップ端
	{12, L"asset/S_Light.png"},		//ライト
	{15, L"asset/demonfish1.png"},	//オニキンメ
	{16, L"asset/Lightfish1.png"},	//アンコウ
	{20, L"asset/S_Lumine.png"}		//光マス
};

GameScene::GameScene(const int _stage) {
	//ステージ番号を保存
	stage = _stage;

	textureManager = new TextureManager(g_pDevice);
	// ステージ選択で選んだ番号のマップデータをロード
	LoadMapData(stage);
	// ステージに合わせてズーム(今はステージ2に合わせてるだけ)
	g_Camera.SetCamera(250.0f, -130.0f, 2.5f);

	game_bg = std::make_unique<Object>();
	if (stage <= 4) {
		game_bg->Init(textureManager, L"asset/BackGround1.png");
	}
	else if (stage >= 5) {
		game_bg->Init(textureManager, L"asset/BackGround2.png");
	}
	game_bg->SetPos(0.0f, 0.0f, 0.0f);
	game_bg->SetSize(1920.0f, 1080.0f, 0.0f);

	for (int i = 0; i < 4; i++) {
		cylinder.emplace_back(std::make_unique<O2>());
		cylinder[i]->Init(textureManager, L"asset/UI/O2_1.png");
		cylinder[i]->SetPos((i * 30.0f) + 530.0f, 0.0f, 0.0f);
		cylinder[i]->SetSize(25.0f, 50.0f, 0.0f);

		o2.emplace_back(std::make_unique<O2>());
		o2[i]->Init(textureManager, L"asset/UI/O2_2.png");
		o2[i]->SetPos((i * 30.0f) + 530.0f, -3.5f, 0.0f);
		o2[i]->SetSize(22.5f, 40.0f, 0.0f);
	}

	c_pos = g_Camera.Camera_Pos;
	pause = std::make_unique<Object>();
	pause->Init(textureManager, L"asset/UI/pause.png");
	pause->SetPos(c_pos.x, c_pos.y - 300.f, 0.0f);
	pause->SetSize(500.0f, 300.0f, 0.0f);
	pause->SetShouldApplyBlur(true);

	for (int i = 0; i < 3; i++) {
		button.emplace_back(std::make_unique<Object>());
		button[i]->Init(textureManager, L"asset/UI/haguruma.png");
		button[i]->SetPos((i * 120.0f) + (c_pos.x - 130.0f), c_pos.y - 305.0f, 0.0f);
		button[i]->SetSize(80.0f, 80.0f, 0.0f);
		button[i]->SetShouldApplyBlur(true);
	}
	button[1]->SetTexture(textureManager, L"asset/UI/setumei.png");
	button[2]->SetTexture(textureManager, L"asset/UI/House.png");

	// ==========オプション==========
	// 設定ウィンドウ
	setting = std::make_unique<Object>();
	setting->Init(textureManager, L"asset/UI/sound_UI.png");
	setting->SetPos(0.0f, 0.0f, 0.0f);
	setting->SetSize(450.0f, 300.0f, 0.0f);

	for (int i = 0; i < 2; i++) {
		sound_cursol.emplace_back(std::make_unique<SoundCursol>());
		sound_cursol[i]->Init(textureManager, L"asset/UI/sound.png");
		sound_cursol[i]->SetPos(-140.0f, (i * -255.0f) + 50.0f, 0.0f);
		sound_cursol[i]->SetSize(100.0f, 100.0f, 0.0f);
	}

	cursol = std::make_unique<Cursol>();
	cursol->Init(textureManager, L"asset/UI/cursol.png");
	cursol->SetPos(-200.0f, 0.0f, 0.0f);
	cursol->SetSize(150.0f, 150.0f, 0.0f);

	close = std::make_unique<Object>();
	close->Init(textureManager, L"asset/UI/batten2.png");
	close->SetPos(300.0f, 230.0f, 0.0f);
	close->SetSize(75.0f, 75.0f, 0.0f);

	// 初期化 (一度だけ実行)
	for (int i = 0; i < 3; i++) {
		buttonParams[i].amplitude = 8.0f + (rand() % 100 - 50) * 0.05f;      // 振幅にランダム値を追加
		buttonParams[i].frequency = 0.01f + (rand() % 100 - 50) * 0.0001f;   // 周波数にランダム値を追加
		buttonParams[i].phase = (rand() % 360) * 0.0174533f;                 // 位相をランダム化 (0 ～ 2π)
	}

}

GameScene::~GameScene() {
	//データの保存
	SaveFile(stage, mendako);

	// mapdataのリソースを解放
	for (auto& row : mapdata) {
		for (auto& obj : row) {
			obj.reset(); // unique_ptr のリソース解放
		}
	}
	mapdata.clear(); // 明示的にベクトルをクリア

	// TextureManagerを解放
	delete textureManager;
}

void GameScene::Update() {
	input.Update();
	if (state == 0) {
		// ゲーム時間の計測開始
		start = std::chrono::high_resolution_clock::now();
		state = 1;
	}
	else if (state == 1) {
		// 現在の時間を取得
		auto now = std::chrono::high_resolution_clock::now();
		// 経過時間を計算
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);


		// 古いマップデータの保存
		oldlist = maplist;

		// マップオブジェクトの更新
		for (const auto& row : mapdata) {
			for (const auto& obj : row) {
				if (obj) {
					maplist = obj->Update(maplist);
				}
			}
		}
		// キャラクターオブジェクトの更新
		for (const auto& obj : characterObj) {
			maplist = obj->Update(maplist);
		}

		// マップ情報更新
		MapUpdate();

		// 制限時間UIの更新
		o2Gauge(elapsed);

		// 死亡判定取得
		for (auto& obj : characterObj) {
			Enemy* enemy = dynamic_cast<Enemy*>(obj.get());
			if (enemy) {  // dynamic_castが成功した場合のみ処理
				deadFlg = enemy->GetState();
				if (deadFlg) {
					break;
				}
			}
		}

		if (input.GetKeyTrigger(VK_P)) {
			state = 2;
		}

		// 死亡していたらシーンチェンジ
		if (deadFlg || input.GetKeyTrigger(VK_3)) {
			// スコアをリザルトに渡して移動
			SceneManager::ChangeScene(SceneManager::RESULT, score);
		}
	}
	else if (state == 3) {
		PauseSelect(&input);
	}
	else if (state == 4) {
		OptionSelect(&input);
	}
	PauseAnimation();
	framecount++;
}

void GameScene::Draw() {
	// 背景
	game_bg->Draw();
	for (const auto& row : mapdata) {
		for (const auto& obj : row) {
			if (obj) {
				obj->Draw();
			}
		}
	}
	for (const auto& obj : characterObj) {

		obj->Draw();
	}

	// UI
	for (const auto& obj : o2) {
		obj->Draw();
	}
	for (const auto& obj : cylinder) {
		obj->Draw();
	}

	if (state >= 2) {
		// ポーズ画面
		pause->Draw();
		for (const auto& obj : button) {
			obj->Draw();
		}
	}
	if (state == 4) {
		setting->Draw();
		for (int i = 0; i < 2; i++) {
			sound_cursol[i]->Draw();
		}
		cursol->Draw();
		close->Draw();
	}
}

void GameScene::LoadMapData(int stage) {
	mapdata.clear();

	std::string stageStr = std::to_string(stage);  // int を文字列に変換
	std::wstring mapPath = L"Data/MAP_STAGE" + std::wstring(stageStr.begin(), stageStr.end()) + L".csv";
	//std::wstring mapPath = L"Data/TestData.csv";

	maplist = Loadmap(mapPath.c_str());

	mapdata.resize(maplist.size()); // 外側のベクトルをリサイズ

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // 各行をリサイズ
		//↑データ入ってる
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != -1 && (objectType == 1 || objectType == 4 || objectType == 11 || objectType == 19 || objectType == 20)) {
				auto obj = CreateObject(objectType, textureManager); // オブジェクト生成
				if (obj) {
					float x = j * 30.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					obj->SetXY(j, i);

					mapdata[i][j] = std::move(obj);
				}
			}
			else if (objectType != -1) {
				auto obj = CreateObject(objectType, textureManager); // オブジェクト生成
				if (obj) {
					float x = j * 30.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					obj->SetXY(j, i);

					characterObj.emplace_back(std::move(obj));
					//maplist[i][j] = -1;
				}
			}
		}
	}
}

std::unique_ptr<Object> GameScene::CreateObject(int objectType, TextureManager* textureManager) {
	std::unique_ptr<Object> obj;
	int u, v;
	int dir = 0;
	//オブジェクトを生成
	switch (objectType) {
	case 0: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	case 1: obj = std::make_unique<Wall>(); u = 1; v = 1; break;
	case 2: obj = std::make_unique<Player>(); u = 4; v = 2; break;
	case 3: obj = std::make_unique<Enemy>(); u = 8; v = 2; break;
	case 4: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	case 5: obj = std::make_unique<Mendako>(); u = 4; v = 2; break;
	case 6: obj = std::make_unique<Kagamidai>(); u = 4; v = 2; break;
	case 7: obj = std::make_unique<Kagamidai>(); u = 4; v = 3; dir = 1; break;
	case 8: obj = std::make_unique<Trap>(); u = 1; v = 1; break;
	case 9: obj = std::make_unique<Kairyu>(); u = 1; v = 1; break;
	case 10: obj = std::make_unique<Kairyu>(); u = 1; v = 1; dir = 1; break;
	case 11: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	case 12: obj = std::make_unique<Light>(); u = 1; v = 1; break;
	case 15: obj = std::make_unique<Onikinme>(); u = 4; v = 1; break;
	case 16: obj = std::make_unique<Ankou>(); u = 4; v = 2; break;
	case 20: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	default: return nullptr;
	}

	//textureMappingに設定したパスを探す
	auto it = textureMapping.find(objectType);
	if (it != textureMapping.end()) {
		obj->Init(textureManager, it->second.c_str(), u, v);
		obj->SetDirection(dir);
	}
	else {
		obj->Init(textureManager, L"asset/default.png");
		//obj->Init(textureManager, L"asset/map_0.png");
	}

	return obj;
}

void GameScene::MapUpdate() {
	//マップデータの更新
	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // 各行をリサイズ
		for (int j = 0; j < maplist[i].size(); ++j) {

			//古いマップデータと比較
			int OldObject = oldlist[i][j];
			int NewObject = maplist[i][j];

			//マップデータが変化しているなら
			if (NewObject != OldObject)
			{
				//古いオブジェクトを削除
				std::cout << "削除" << std::endl;
				if (NewObject == 0) {
					mapdata[i][j] = CreateObject(NewObject, textureManager);
				}

				// ↓重かった原因↓：if文の中に入れて変化時だけにしたらちょっと軽くなった
				int objectType = maplist[i][j];
				if (objectType != -1 && (objectType == 20 || objectType == 11 || objectType == 12 || objectType == 0)) {
					auto obj = CreateObject(objectType, textureManager); // 関数でオブジェクト生成
					if (obj) {
						float x = j * 30.0f;	// x座標		列 * Objectの大きさ * オフセット	
						float y = i * -30.0f;	// y座標		行 * Objectの大きさ * オフセット

						obj->SetPos(x, y, 0.0f);
						obj->SetSize(30.0f, 30.0f, 0.0f);
						obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
						obj->SetXY(j, i);

						mapdata[i][j] = std::move(obj);
					}
				}
			}
		}
	}
}

void GameScene::PauseSelect(Input* input) {
	static int selectbutton = 0;
	if (input->GetKeyTrigger(VK_LEFT)) {
		selectbutton--;
		if (selectbutton < 0) {
			selectbutton = 2;
		}
	}
	if (input->GetKeyTrigger(VK_RIGHT)) {
		selectbutton++;
		if (selectbutton > 2) {
			selectbutton = 0;
		}
	}
	if (input->GetKeyTrigger(VK_P)) {
		state = 4;
	}
	for (int i = 0; i < 3; i++) {
		button[i]->SetSize(80.0f, 80.0f, 0.0f);
	}
	button[selectbutton]->SetSize(100.0f, 100.0f, 0.0f);

	if (input->GetKeyTrigger(VK_RETURN)) {
		switch (selectbutton) {
			// オプション
		case 0:
			break;
			// 操作説明
		case 1:
			break;
			// ステージ選択に戻る
		case 2:
			break;
		}
	}
}

void GameScene::PauseAnimation() {
	if (state == 2) {
		if (pause->GetPos().y < c_pos.y + 0.0f) {
			pause->SetPos(c_pos.x, pause->GetPos().y + 80.0f, 0.0f);
			for (int i = 0; i < 3; i++) {
				button[i]->SetPos((i * 110.0f) + (c_pos.x - 110.0f), button[i]->GetPos().y + 80.0f, 0.0f);
			}
		}
		else if (pause->GetPos().y >= c_pos.y + 0.0f) {
			pause->SetPos(c_pos.x, c_pos.y, 0.0f);
			for (int i = 0; i < 3; i++) {
				button[i]->SetPos((i * 110.0f) + (c_pos.x - 110.0f), c_pos.y - 5.0f, 0.0f);
			}
			state = 3;
		}
	}
	else if (state == 4) {
		if (pause->GetPos().y > c_pos.y - 500.0f) {
			pause->SetPos(c_pos.x, pause->GetPos().y - 80.0f, 0.0f);
			for (int i = 0; i < 3; i++) {
				button[i]->SetPos((i * 110.0f) + (c_pos.x - 110.0f), button[i]->GetPos().y - 80.0f, 0.0f);
			}
		}
		else if (pause->GetPos().y <= -500.0f) {
			state = 1;
		}
	}

	if (state == 3) {
		// 毎フレームの更新
		for (int i = 0; i < 3; i++) {
			// 初期位置
			DirectX::XMFLOAT3 initialPos((i * 110.0f) + (c_pos.x - 110.0f), c_pos.y - 5.0f, 0.0f);

			// ボタンごとの揺れパラメータを使用
			float offsetX = buttonParams[i].amplitude * sin(framecount * buttonParams[i].frequency + buttonParams[i].phase);
			float offsetY = buttonParams[i].amplitude * 0.5f * sin(framecount * buttonParams[i].frequency * 1.2f + buttonParams[i].phase * 0.5f);

			// 位置を設定
			button[i]->SetPos(initialPos.x + offsetX, initialPos.y + offsetY, initialPos.z);
		}
	}
}

void GameScene::o2Gauge(std::chrono::milliseconds time) {
	for (const auto& obj : o2) {
		obj->Update();
	}
	for (const auto& obj : cylinder) {
		obj->Update();
	}

	static int lastCheckedTime = 0;
	float remainingTime = (MAXTIME / 3) - (time.count() - lastCheckedTime);

	if (o2.size() == 1) {
		lastCheckedTime = time.count();  // 新しいボンベ用に時間をリセット
	}

	if (remainingTime > 0.0f) {

		// 遭難者に付いてくる用
		for (const auto& obj : characterObj) {
			Player* playerObj = dynamic_cast<Player*>(obj.get());
			if (playerObj) {
				DirectX::XMFLOAT3 pos = playerObj->GetPos();
				cylinder.back()->SetPos(pos.x + 20.0f, pos.y + 20.0f, pos.z);
				cylinder.back()->SetSize(15.0f, 36.0f, 0.0f);
				o2.back()->SetPos(pos.x + 20.0f, pos.y + 17.5f, pos.z);
				o2.back()->SetSize(12.0f, 27.6f, 0.0f);
				break;  // 見つかったらループを抜ける
			}
		}

		float sizeRatio = (remainingTime / (MAXTIME / 3)) * 27.6f;
		if (sizeRatio <= 0.0f) {
			sizeRatio = 0.0f;
		}

		// ボンベの基準位置（底の位置固定）
		float baseY = o2.back()->GetPos().y;  // ボンベの初期位置

		// 縮小分だけボンベの位置を上に移動（0 〜 27.6 の範囲）
		float newY = baseY - (27.6f - sizeRatio) / 2.0f;

		// 新しいサイズと位置をセット（上に向かって縮む）
		o2.back()->SetSize(12.0f, sizeRatio, 0.0f);
		o2.back()->SetPos(o2.back()->GetPos().x, newY, 0.0f);
	}

	// ボンベ削除処理
	if (remainingTime <= 0.0f) {
		if (cylinder.size() > 1) {
			o2.back()->SetState(2);
			cylinder.back()->SetState(2);
			if (cylinder.back()->GetPos().y < -500.0f) {
				cylinder.erase(cylinder.end() - 1);
				o2.erase(o2.end() - 1);
				lastCheckedTime = time.count();  // 新しいボンベ用に時間をリセット
			}
		}
	}


}

void GameScene::OptionSelect(Input* input) {
	static int select = 1;
	if (input->GetKeyTrigger(VK_UP)) {
		select--;
		if (select < 0) {
			select = 2;
		}
	}
	if (input->GetKeyTrigger(VK_DOWN)) {
		select++;
		if (select > 2) {
			select = 0;
		}
	}
	float cursol_move = sin(framecount / 180.0f * 3.14) * 15.0f;
	close->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	switch (select) {
	case 0:
		cursol->SetPos((c_pos.x - 20.0f), (c_pos.y - 20.0f) + cursol_move, 0.0f);
		close->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		if (input->GetKeyTrigger(VK_RETURN))
		{
			state = 1;
		}
		break;
	case 1: cursol->SetPos(c_pos.x - 30.0f, c_pos.y - 50.0f + cursol_move, 0.0f);
		g_Sound.SetVolBGM(sound_cursol[0]->Update(input));
		break;
	case 2: cursol->SetPos(c_pos.x - 30.0f, c_pos.y - 20.0f + cursol_move, 0.0f);
		g_Sound.SetVolSE(sound_cursol[1]->Update(input));
		break;
	}
}