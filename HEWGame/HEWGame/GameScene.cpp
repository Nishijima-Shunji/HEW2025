#include "GameScene.h"
#include "Game.h"
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

// textureMappingの初期化
	//マップからオブジェクトを生成する際に参照するキー
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},	//無
	{1, L"asset/S_Wall.png"},	//壁
	{2, L"asset/S_Player.png"},	//プレイヤー
	{3, L"asset/S_Light.png"},	//ライト
	{4, L"asset/S_Enemy.png"},	//敵
	{5, L"asset/S_Lumine.png"}	//発光
};

GameScene::GameScene() {
	textureManager = new TextureManager(g_pDevice);
	// マップデータをロード
	LoadMapData();
}

GameScene::~GameScene() {
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

	//古いマップデータの保存
	oldlist = maplist;

	for (const auto& row : mapdata) {
		for (const auto& obj : row) {
			if (obj) {
				maplist = obj->Update(maplist);
			}
		}
	}

	for (const auto& obj : characterObj) {
		obj->Update(maplist);
	}

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
				mapdata[i][j] = CreateObject(NewObject, textureManager);

				// ↓重かった原因↓：if文の中に入れて変化時だけにしたらちょっと軽くなった
				int objectType = maplist[i][j];
				if (objectType != -1) {
					auto obj = CreateObject(objectType, textureManager); // Factory関数でオブジェクト生成
					if (obj) {
						float x = j * 30.0f - 500.0f; // x座標		列 * Objectの大きさ * オフセット
						float y = i * -30.0f + 280.0f; // y座標		行 * Objectの大きさ * オフセット

						obj->SetPos(x, y, 0.0f);
						obj->SetSize(30.0f, 30.0f, 0.0f);
						obj->SetAngle(0.0f);
						obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

						mapdata[i][j] = std::move(obj);
					}
				}
			}
		}
	}

	if (input.GetKeyTrigger(VK_3)) {
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw() {
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
}

void GameScene::LoadMapData() {
	mapdata.clear();

	// マップデータをCSVから読み込む
	maplist = Loadmap("Data/TestData.csv");
	mapdata.resize(maplist.size()); // 外側のベクトルをリサイズ

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // 各行をリサイズ
		//↑データ入ってる
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != -1 && (objectType == 1 || objectType == 3)) {
				auto obj = CreateObject(objectType, textureManager); // オブジェクト生成
				if (obj) {
					float x = j * 30.0f - 500.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f + 280.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

					mapdata[i][j] = std::move(obj);
				}
			}
			else if (objectType != -1 && (objectType == 2 || objectType == 4)) {
				auto obj = CreateObject(objectType, textureManager); // オブジェクト生成
				if (obj) {
					float x = j * 30.0f - 500.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f + 280.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

					characterObj.emplace_back(std::move(obj));
					maplist[i][j] = -1;
				}
			}
		}
	}
}

std::unique_ptr<Object> GameScene::CreateObject(int objectType, TextureManager* textureManager) {
	std::unique_ptr<Object> obj;

	//オブジェクトを生成
	switch (objectType) {
	case 0: obj = std::make_unique<Object>(); break;
	case 1: obj = std::make_unique<Wall>(); break;
	case 2: obj = std::make_unique<Player>(); break;
	case 3: obj = std::make_unique<Light>(); break;
	case 4: obj = std::make_unique<Enemy>(); break;
	case 5: obj = std::make_unique<Object>(); break;
	default: return nullptr;
	}

	//textureMappingに設定したパスを探す
	auto it = textureMapping.find(objectType);
	if (it != textureMapping.end()) {
		obj->Init(textureManager, it->second.c_str());
	}
	else {
		obj->Init(textureManager, L"asset/default.png");
		//obj->Init(textureManager, L"asset/map_0.png");
	}

	return obj;
}