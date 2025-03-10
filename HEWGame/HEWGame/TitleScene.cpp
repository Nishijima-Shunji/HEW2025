#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()とsrand()のため
#include <ctime>    // time()のため

TitleScene::TitleScene(int num) : state(num) {
	textureManager = new TextureManager(g_pDevice);

	// ロゴ表示
	logo = std::make_unique<Object>();
	logo->Init(textureManager, L"asset/logo.png");
	logo->SetPos(0.0f, 0.0f, 0.0f);
	logo->SetSize(800.0f, 800.0f, 0.0f);
	logo->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (state == 1) {
		InitRoad();
	}
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
		float width_konbu = 10.0f * sizeFactor_Bg;		// 昆布の幅
		float height_konbu = 10.0f * sizeFactor_Bg;		// 高さ
		obj->SetPos(x, y, 1.0f);						// 位置を設定
		obj->SetSize(width_konbu, height_konbu, 0.0f);  // 大きさを設定
		obj->SetAngle(0.0f);							// 角度を設定
		obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);			// 色を設定
		title_Ob.push_back(obj);
	}
}

void TitleScene::Update() {
	input.Update();
	//	=====ロゴ表示中に読み込み=====
	if (state == 0) {
		// タイトルに切り替わるまでのアニメーション
		InitAnimation();
	}
	// =====タイトル画面=====
	else if (state == 1) {
		// タイトルの操作
		Select(&input);
		if (input.GetKeyTrigger(VK_M)) {
			g_Sound.StopBGM();
			g_Sound.ReleaseBGM();
			g_Sound.PlayBGM();
		}
	}
	else if (state == 2) {
		// オプション
		OptionSelect(&input);
	}
	if (state >= 1) {
		// 背景アニメーション
		BGanimation();
	}
	framecount++;
}

// 各シーンの描画
void TitleScene::Draw() {
	if (state == 0) {
		logo->Draw();
	}
	else if (state >= 1) {
		title_bg->Draw();
		title_name->Draw();
		for (auto& obj : window) {
			obj->Draw();
		}
		for (auto& obj : icon) {
			obj->Draw();
		}
		for (auto& obj : button) {
			obj->Draw();
		}
		light->Draw();
		if (state == 2) {
			setting->Draw();
			cursol->Draw();
			close->Draw();
			for (auto& obj : sound_cursol) {
				obj->Draw();
			}
		}
	}
}

void TitleScene::InitAnimation() {
	static int count = 0;
	if (count == 0) {
		InitRoad();
	}
	// 徐々にロゴを消していく
	logo->SetColor(1.0f, 1.0f, 1.0f, logo->GetColor().w - 0.01f);
	if (logo->GetColor().w <= 0) {
		state = 1;
	}
	count++;
}

void TitleScene::InitRoad() {
	// タイトル背景====================
	title_bg = new Object;
	title_bg->Init(textureManager, L"asset/title/title 2_000.png");
	title_bg->SetPos(0.0f, 0.0f, 0.0f);         // 位置を設定
	title_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // 大きさを設定

	// タイトル名=======================
	title_name = new Object;
	title_name->Init(textureManager, L"asset/title.png");
	title_name->SetPos(0.0f, 250.0f, 1.0f);       // 位置を設定
	title_name->SetSize(993.0f, 315.0f, 0.0f);  // 大きさを設定

	// ボタン生成
	for (int i = 0; i < 3; i++) {
		button.emplace_back(std::make_unique<Object>());
		button[i]->SetPos((i * 375.0f) - 375.0f, -175.0f, 0.0f);
		button[i]->SetSize(324.0f, 384.0f, 0.0f);

		window.emplace_back(std::make_unique<Object>());
		window[i]->Init(textureManager, L"asset/UI/window.png");
		window[i]->SetPos((i * 375.0f) - 375.0f, -145.0f, 0.0f);
		window[i]->SetSize(200.0f, 200.0f, 0.0f);

		icon.emplace_back(std::make_unique<Object>());
		icon[i]->SetPos((i * 375.0f) - 375.0f, -145.0f, 0.0f);
		icon[i]->SetSize(150.0f, 150.0f, 0.0f);
	}
	button[0]->Init(textureManager, L"asset/UI/OPTION.png");
	button[1]->Init(textureManager, L"asset/UI/START.png");
	button[2]->Init(textureManager, L"asset/UI/EXIT.png");
	icon[0]->Init(textureManager, L"asset/UI/haguruma.png");
	icon[1]->Init(textureManager, L"asset/UI/mendako_icon.png");
	icon[2]->Init(textureManager, L"asset/UI/batten.png");

	// light表示
	light = std::make_unique<Object>();
	light->Init(textureManager, L"asset/UI/FrashLight.png");
	light->SetPos(-375.0f, -350.0f, 0.0f);
	light->SetSize(500.0f, 500.0f, 0.0f);
	light->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// 設定ウィンドウ
	setting = std::make_unique<Object>();
	setting->Init(textureManager, L"asset/UI/sound_UI.png");
	setting->SetPos(0.0f, 0.0f, 0.0f);
	setting->SetSize(900.0f, 600.0f, 0.0f);

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

	// BGM再生
	g_Sound.RoadBGM(BGM_Title);
	g_Sound.SetVolBGM(0.05f);
	g_Sound.PlayBGM();
	g_Sound.SetVolSE(0.05f);
}

void TitleScene::BGanimation() {
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
			title_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
}

void TitleScene::Select(Input* input) {
	//static DirectX::XMFLOAT2 stick_old = { 0.0f, 0.0f }; // 前フレームのスティック状態
	DirectX::XMFLOAT2 stick = input->GetLeftAnalogStick(); // 現在のスティック状態

	// 選択先と今の位置が異なるなら移動開始
	if (nowButton != selectButton) {
		move = true;
	}
	else {
		move = false;
	}
	if (move) {
		if (nowButton < selectButton) {
			DirectX::XMFLOAT3 pos = light->GetPos();
			pos.x += 125.0f;
			light->SetPos(pos.x, pos.y, pos.z);
		}
		else
		{
			DirectX::XMFLOAT3 pos = light->GetPos();
			pos.x -= 125.0f;
			light->SetPos(pos.x, pos.y, pos.z);
		}
	}
	else {
		if (input->GetKeyTrigger(VK_A) || (stick.x < 0.7f && trigger) || input->GetButtonTrigger(XINPUT_LEFT)) {
			if (nowButton > 1) {
				selectButton--;
				g_Sound.PlaySE(SE_CursolMove1);
			}
		}
		if (input->GetKeyTrigger(VK_D) || (stick.x > 0.7f && trigger) || input->GetButtonTrigger(XINPUT_RIGHT)) {
			if (nowButton < 3) {
				selectButton++;
				g_Sound.PlaySE(SE_CursolMove1);
			}
		}
	}

	// 目的地と今の位置がだいたい同じなら停止
	if (abs((button[selectButton - 1]->GetPos().x - light->GetPos().x)) < 10.0f) {
		nowButton = selectButton;
	}

	// ボタンの全サイズをリセット
	for (int i = 0; i < 3; i++) {
		button[i]->SetSize(324.0f, 384.0f, 0.0f);
		window[i]->SetSize(200.0f, 200.0f, 0.0f);
		icon[i]->SetSize(150.0f, 150.0f, 0.0f);
	}

	// 選択中のボタンを強調
	button[nowButton - 1]->SetSize(388.8f, 460.8f, 0.0f);
	window[nowButton - 1]->SetSize(240.0f, 240.0f, 0.0f);
	icon[nowButton - 1]->SetSize(180.0f, 180.0f, 0.0f);

	switch (nowButton) {
	case 1:
		icon[0]->SetAngle(icon[0]->GetAngle() + 2.0f);
		icon[1]->SetAngle(0.0f);
		icon[2]->SetAngle(0.0f);
		break;
	case 2:
		icon[1]->SetAngle(icon[1]->GetAngle() + 2.0f);
		icon[0]->SetAngle(0.0f);
		icon[2]->SetAngle(0.0f);
		break;
	case 3:
		icon[2]->SetAngle(icon[2]->GetAngle() + 2.0f);
		icon[0]->SetAngle(0.0f);
		icon[1]->SetAngle(0.0f);
		break;
	}

	// シーンの切り替えがあるから一番最後に置く
	if (input->GetKeyTrigger(VK_RETURN) || input->GetButtonTrigger(XINPUT_A)) {
		switch (nowButton) {
		case 1: g_Sound.PlaySE(SE_CursolMove2); state = 2; break;
		case 2:
			g_Sound.PlaySE(SE_Confilm);
			g_Sound.StopBGM();
			g_Sound.ReleaseBGM();
			SceneManager::ChangeScene(SceneManager::SELECT);
			break;
		case 3: SendMessage(GetGameWindowHandle(), WM_CLOSE, 0, 0); break;
		}
	}
}

void TitleScene::OptionSelect(Input* input) {
	static int select = 1;
	DirectX::XMFLOAT2 stick = input->GetLeftAnalogStick();
	if (input->GetKeyTrigger(VK_W) || input->GetButtonTrigger(XINPUT_UP)) {
		select--;
		// カーソル移動音
		g_Sound.PlaySE(SE_CursolMove1);
		// ボタン移動
		if (select < 0) {
			select = 2;
		}
	}
	if (input->GetKeyTrigger(VK_S) || input->GetButtonTrigger(XINPUT_DOWN)) {
		select++;
		// カーソル移動音
		g_Sound.PlaySE(SE_CursolMove1);
		if (select > 2) {
			select = 0;
		}
	}
	// 閉じる
	if (input->GetButtonTrigger(XINPUT_B)) {
		g_Sound.PlaySE(SE_CursolMove2);
		state = 1;
	}

	// クリオネふわふわ
	float cursol_move = sin(framecount / 180.0f * 3.14) * 15.0f;

	// カーソル位置による動作
	switch (select) {
	case 0:
		cursol->SetPos(220.0f, 230.0f + cursol_move, 0.0f);
		close->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
		// 閉じる
		if (input->GetKeyTrigger(VK_RETURN) || input->GetButtonTrigger(XINPUT_A))
		{
			g_Sound.PlaySE(SE_CursolMove2);
			state = 1;
		}
		break;
	case 1: cursol->SetPos(-300.0f, 50.0f + cursol_move, 0.0f);
		close->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		// BGMvol
		g_Sound.SetVolBGM(sound_cursol[0]->Update(input));
		break;
	case 2: cursol->SetPos(-300.0f, -200.0f + cursol_move, 0.0f);
		close->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		// SEvol
		g_Sound.SetVolSE(sound_cursol[1]->Update(input));
		break;
	}
}

