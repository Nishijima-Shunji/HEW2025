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

// ステージの経過時間計測用変数
std::chrono::high_resolution_clock::time_point start;

// textureMappingの初期化
	//マップからオブジェクトを生成する際に参照するキー
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},		//無
	{1, L"asset/Wall.png"},		//壁
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
	for (int i = 0; i < 4; i++) {
		cylinder.emplace_back(std::make_unique<O2>());
		cylinder[i]->Init(textureManager, L"asset/O2_1.png");
		cylinder[i]->SetPos((i * 50.0f) + 500.0f, +300.0f, 0.0f);
		cylinder[i]->SetSize(50.0f, 100.0f, 0.0f);

		o2.emplace_back(std::make_unique<O2>());
		o2[i]->Init(textureManager, L"asset/O2_2.png");
		o2[i]->SetPos((i * 50.0f) + 500.0f, 290.0f, 0.0f);
		o2[i]->SetSize(45.0f, 80.0f, 0.0f);
	}
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
			maplist = obj->Update(maplist);
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
					if (NewObject == 0) {
						mapdata[i][j] = CreateObject(NewObject, textureManager);
					}

					// ↓重かった原因↓：if文の中に入れて変化時だけにしたらちょっと軽くなった
					int objectType = maplist[i][j];
					if (objectType != -1 && (objectType == 20 || objectType == 11 || objectType == 19 || objectType == 0)) {
						auto obj = CreateObject(objectType, textureManager); // 関数でオブジェクト生成
						if (obj) {
							//float x = j * 30.0f - 500.0f;	// x座標		列 * Objectの大きさ * オフセット		※カメラあればオフセット要らないかも
							float x = j * 30.0f;	// x座標		列 * Objectの大きさ * オフセット		※カメラあればオフセット要らないかも
							//float y = i * -30.0f + 280.0f;	// y座標		行 * Objectの大きさ * オフセット
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

		o2Gauge(elapsed);

		if (input.GetKeyTrigger(VK_3)) {
			// スコアをリザルトに渡して移動
			SceneManager::ChangeScene(SceneManager::RESULT, score);
		}
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
	for (const auto& obj : o2) {
		obj->Draw();
	}
	for (const auto& obj : cylinder) {
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
	case 15: obj = std::make_unique<Onikinme>(); u = 4; v = 1; break;
	case 16: obj = std::make_unique<Ankou>(); u = 4; v = 2; break;
	case 19: obj = std::make_unique<Light>(); u = 1; v = 1; break;
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

void GameScene::o2Gauge(std::chrono::milliseconds time) {
	for (const auto& obj : o2) {
		obj->Update();
	}

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
	static int lastCheckedTime = 0;
	float remainingTime = (MAXTIME / 3) - (time.count() - lastCheckedTime);

	if (remainingTime > 0.0f && o2.size() > 1) {
		float sizeRatio = (remainingTime / (MAXTIME / 3)) * 27.6f;

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
		if (o2.size() > 1) {
			cylinder.erase(cylinder.end() - 1);
			o2.erase(o2.end() - 1);
			lastCheckedTime = time.count();  // 新しいボンベ用に時間をリセット
		}
	}


}

