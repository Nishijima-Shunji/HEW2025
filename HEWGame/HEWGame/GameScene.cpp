#include "GameScene.h"
#include "Game.h"
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ankou.h"
#include "Kagamidai.h"
#include "Kairyu.h"
#include "Mendako.h"
#include "Onikinme.h"
#include "Trap.h"

// textureMappingの初期化
	//マップからオブジェクトを生成する際に参照するキー
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},		//無
	{1, L"asset/S_Wall.png"},		//壁
	{2, L"asset/survivor3.png"},	//プレイヤー
	{3, L"asset/shake1.png"},		//敵
	{4, L"asset/S_Goal.png"},		//ゴール
	{5, L"asset/mendako.png"},	//メンダコ
	{6, L"asset/mirror_fish.png"},	//鏡鯛
	{7, L"asset/mirror_fish.png"},	//鏡鯛
	{8, L"asset/S_trap.png"},		//トラップ
	{9, L"asset/S_Kairyu.png"},		//海流
	{10, L"asset/S_Kairyu.png"},		//海流
	{11, L"asset/S_hasi.png"},		//マップ端
	{15, L"asset/demonfish1.png"},	//オニキンメ
	{16, L"asset/Lightfish1.png"},		//アンコウ
	{19, L"asset/S_Light.png"},		//ライト
	{20, L"asset/S_Lumine.png"}		//光マス
};

GameScene::GameScene(int stage) {
	textureManager = new TextureManager(g_pDevice);
	// ステージ選択で選んだ番号のマップデータをロード
	LoadMapData(stage);


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
						float x = j * 30.0f - 500.0f;	// x座標		列 * Objectの大きさ * オフセット		※カメラあればオフセット要らないかも
						float y = i * -30.0f + 280.0f;	// y座標		行 * Objectの大きさ * オフセット

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
		// スコアをリザルトに渡して移動
		SceneManager::ChangeScene(SceneManager::RESULT,score);
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
					float x = j * 30.0f - 500.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f + 280.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

					mapdata[i][j] = std::move(obj);
				}
			}
			else if (objectType != -1) {
				auto obj = CreateObject(objectType, textureManager); // オブジェクト生成
				if (obj) {
					float x = j * 30.0f - 500.0f; // x座標		列 * Objectの大きさ * オフセット
					float y = i * -30.0f + 280.0f; // y座標		行 * Objectの大きさ * オフセット

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

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
	//オブジェクトを生成
	switch (objectType) {
	case 0: obj = std::make_unique<Object>(); u = 1; v = 1;  break;
	case 1: obj = std::make_unique<Wall>(); u = 1; v = 1; break;
	case 2: obj = std::make_unique<Player>(); u = 4; v = 2; break;
	case 3: obj = std::make_unique<Enemy>(); u = 8; v = 2; break;
	case 4: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	case 5: obj = std::make_unique<Mendako>(); u = 4; v = 2; break;
	case 6: obj = std::make_unique<Kagamidai>(); u = 4; v = 2; break;
	case 7: obj = std::make_unique<Kagamidai>(); u = 4; v = 3; break;
	case 8: obj = std::make_unique<Trap>(); u = 1; v = 1; break;
	case 9: obj = std::make_unique<Kairyu>(); u = 1; v = 1; break;
	case 10: obj = std::make_unique<Kairyu>(); u = 1; v = 1; break;
	case 11: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	case 15: obj = std::make_unique<Onikinme>(); u = 4; v = 1; break;
	case 16: obj = std::make_unique<Ankou>(); u = 4; v = 2; break;
	case 19: obj = std::make_unique<Light>(); u = 1; v = 1; break;
	case 20: obj = std::make_unique<Object>(); u = 1; v = 1; break;
	default: return nullptr;
	}

	//textureMappingに設定したパスを探す
	auto it = textureMapping.find(objectType);
	if (it != textureMapping.end()) {
		obj->Init(textureManager, it->second.c_str() , u , v);
	}
	else {
		obj->Init(textureManager, L"asset/default.png");
		//obj->Init(textureManager, L"asset/map_0.png");
	}

	return obj;
}