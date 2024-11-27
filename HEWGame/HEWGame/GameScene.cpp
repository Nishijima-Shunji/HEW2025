#include "GameScene.h"
#include "Game.h"
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

// textureMappingの初期化
	//マップからオブジェクトを生成する際に参照するキー
static std::unordered_map<int, std::wstring> textureMapping = {
	{1, L"asset/wall.png"},		//壁
	{2, L"asset/player.png"},	//プレイヤー
	{3, L"asset/enemy.png"}		//敵
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
}

void GameScene::LoadMapData() {
	mapdata.clear();

	// マップデータをCSVから読み込む
	maplist = Loadmap("Data/TestData.csv");
	mapdata.resize(maplist.size()); // 外側のベクトルをリサイズ

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // 各行をリサイズ
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != 0) {
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

std::unique_ptr<Object> GameScene::CreateObject(int objectType, TextureManager* textureManager) {
	std::unique_ptr<Object> obj;

	//オブジェクトを生成
	switch (objectType) {
	case 1: obj = std::make_unique<Player>(); break;
	case 2: obj = std::make_unique<Wall>(); break;
	case 3: obj = std::make_unique<Enemy>(); break;
	default: return nullptr;
	}

	//textureMappingに設定したパスを探す
	auto it = textureMapping.find(objectType);
	if (it != textureMapping.end()) {
		obj->Init(textureManager, it->second.c_str());
	}
	else {
		obj->Init(textureManager, L"asset/default.png");
	}

	return obj;
}

