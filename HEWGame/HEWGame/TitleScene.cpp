#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()��srand()�̂���
#include <ctime>    // time()�̂���

TitleScene::TitleScene(int num) : state(num) {
	textureManager = new TextureManager(g_pDevice);

	// ���S�\��
	logo = std::make_unique<Object>();
	logo->Init(textureManager, L"asset/logo.png");
	logo->SetPos(0.0f, 0.0f, 0.0f);
	logo->SetSize(800.0f, 800.0f, 0.0f);
	logo->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (state = 1) {
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
	g_Sound.ReleaseBGM();
	g_Sound.ReleaseSE();
}

void TitleScene::InitTitleObjects(int count) {
	TextureManager* textureManager = new TextureManager(g_pDevice);
	srand(static_cast<unsigned>(time(0)));  // �����_���������̂��߂̃V�[�h

	for (int i = 0; i < count; ++i) {
		Object* obj = new Object;
		obj->Init(textureManager, L"asset/Bg/konbu.png", 8, 4);
		float x = static_cast<float>((rand() % 1000) - 500);  // �����_����x�ʒu
		float y = static_cast<float>((rand() % 500) - 400);   // �����_����y�ʒu
		// y�̒l���������قǑ傫������
		float sizeFactor_Bg = 1.0f + (25.0f - y) / 25.0f;  // y���������ق�sizeFactor���傫���Ȃ�
		float width_konbu = 10.0f * sizeFactor_Bg;		// ���z�̕�
		float height_konbu = 10.0f * sizeFactor_Bg;		// ����
		obj->SetPos(x, y, 1.0f);						// �ʒu��ݒ�
		obj->SetSize(width_konbu, height_konbu, 0.0f);  // �傫����ݒ�
		obj->SetAngle(0.0f);							// �p�x��ݒ�
		obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);			// �F��ݒ�
		title_Ob.push_back(obj);
	}
}

void TitleScene::Update() {
	input.Update();
	//	=====���S�\�����ɓǂݍ���=====
	if (state == 0) {
		// �^�C�g���ɐ؂�ւ��܂ł̃A�j���[�V����
		InitAnimation();
	}
	// =====�^�C�g�����=====
	else if (state == 1) {
		// �^�C�g���̑���
		Select(&input);
	}
	else if (state == 2) {
		// �I�v�V����
		OptionSelect(&input);
	}
	if (state >= 1) {
		// �w�i�A�j���[�V����
		BGanimation();
	}
	framecount++;
}

// �e�V�[���̕`��
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
	InitRoad();
	// ���X�Ƀ��S�������Ă���
	logo->SetColor(1.0f, 1.0f, 1.0f, logo->GetColor().w - 0.01f);
	if (logo->GetColor().w <= 0) {
		state = 1;
	}
}

void TitleScene::InitRoad() {
	// �^�C�g���w�i====================
	title_bg = new Object;
	title_bg->Init(textureManager, L"asset/title/title 2_000.png");
	title_bg->SetPos(0.0f, 0.0f, 0.0f);         // �ʒu��ݒ�
	title_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // �傫����ݒ�

	// �^�C�g����=======================
	title_name = new Object;
	title_name->Init(textureManager, L"asset/title.png");
	title_name->SetPos(0.0f, 250.0f, 1.0f);       // �ʒu��ݒ�
	title_name->SetSize(993.0f, 315.0f, 0.0f);  // �傫����ݒ�

	// �{�^������
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

	// light�\��
	light = std::make_unique<Object>();
	light->Init(textureManager, L"asset/UI/FrashLight.png");
	light->SetPos(-375.0f, -350.0f, 0.0f);
	light->SetSize(500.0f, 500.0f, 0.0f);
	light->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �ݒ�E�B���h�E
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
		// ���O�ɓǂݍ���
		for (int i = 0; i < 300; i++) {
			if (i % 5 == 0) {
				std::wstring texturePath = L"asset/title/title 2_";
				std::wstring tmp = L"000" + std::to_wstring(i);	// 3���ɒ���   
				tmp = tmp.substr(tmp.size() - 3);  // �Ō��3���݂̂��g�p
				texturePath += tmp;
				texturePath += L".png";
				title_bg->SetTexture(textureManager, texturePath.c_str());
			}
		}
	}

	// BGM�Đ�
	g_Sound.RoadBGM(BGM01);
	g_Sound.SetVolBGM(0.05f);
	g_Sound.PlayBGM();
}

void TitleScene::BGanimation() {
	// �A�j���[�V����
	if (framecount % 1 == 0) {
		int textureIndex = (framecount / 1) % 300;  // 0 ���� 299 �͈̔͂Ƀ��}�b�v
		// ����5�t���[����1�A�j���[�V������
		if (textureIndex % 5 == 0) {
			// ���݂̃A�j���[�V�����ɑΉ�����p�X�ɑg�ݍ��킹��
			std::wstring texturePath = L"asset/title/title 2_";
			std::wstring tmp = L"000" + std::to_wstring(textureIndex);	// 3���ɒ���   
			tmp = tmp.substr(tmp.size() - 3);  // �Ō��3���݂̂��g�p
			texturePath += tmp;
			texturePath += L".png";
			title_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
}

void TitleScene::Select(Input* input) {
	//static DirectX::XMFLOAT2 stick_old = { 0.0f, 0.0f }; // �O�t���[���̃X�e�B�b�N���
	DirectX::XMFLOAT2 stick = input->GetLeftAnalogStick(); // ���݂̃X�e�B�b�N���

	//float threshold = 0.1f; // �������l��ݒ�
	//bool neutral = (abs(stick.x) <= threshold && abs(stick.y) <= threshold);

	//if (neutral && !trigger) {
	//	trigger = true; // �g���K�[���I��
	//}
	//else if (!neutral && trigger) {
	//	trigger = false; // �g���K�[���I�t
	//}

	//stick_old = stick; // ���݂̃X�e�B�b�N��Ԃ�ۑ�


	// �I���ƍ��̈ʒu���قȂ�Ȃ�ړ��J�n
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
		if (input->GetKeyTrigger(VK_LEFT) || (stick.x < 0.7f && trigger) || input->GetButtonTrigger(XINPUT_LEFT)) {
			if (nowButton > 1) {
				selectButton--;
			}
		}
		if (input->GetKeyTrigger(VK_RIGHT) || (stick.x > 0.7f && trigger) || input->GetButtonTrigger(XINPUT_RIGHT)) {
			if (nowButton < 3) {
				selectButton++;
			}
		}
	}

	// �ړI�n�ƍ��̈ʒu���������������Ȃ��~
	if (abs((button[selectButton - 1]->GetPos().x - light->GetPos().x)) < 10.0f) {
		nowButton = selectButton;
	}

	// �{�^���̑S�T�C�Y�����Z�b�g
	for (int i = 0; i < 3; i++) {
		button[i]->SetSize(324.0f, 384.0f, 0.0f);
		window[i]->SetSize(200.0f, 200.0f, 0.0f);
		icon[i]->SetSize(150.0f, 150.0f, 0.0f);
	}

	// �I�𒆂̃{�^��������
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

	// �V�[���̐؂�ւ������邩���ԍŌ�ɒu��
	if (input->GetKeyTrigger(VK_RETURN) || input->GetButtonTrigger(XINPUT_A)) {
		switch (nowButton) {
		case 1: state = 2; break;
		case 2: SceneManager::ChangeScene(SceneManager::SELECT); break;
		case 3: SendMessage(GetGameWindowHandle(), WM_CLOSE, 0, 0); break;
		}
	}
}

void TitleScene::OptionSelect(Input* input) {
	static int select = 1;
	DirectX::XMFLOAT2 stick = input->GetLeftAnalogStick();
	if (input->GetKeyTrigger(VK_UP) || input->GetButtonTrigger(XINPUT_UP)) {
		select--;
		if (select < 0) {
			select = 2;
		}
	}
	if (input->GetKeyTrigger(VK_DOWN) || input->GetButtonTrigger(XINPUT_DOWN)) {
		select++;
		if (select > 2) {
			select = 0;
		}
	}
	if (input->GetButtonTrigger(XINPUT_B)) {
		state = 1;
	}
	float cursol_move = sin(framecount / 180.0f * 3.14) * 15.0f;
	switch (select) {
	case 0:
		cursol->SetPos(220.0f, 230.0f + cursol_move, 0.0f);
		close->SetColor(1.0f, 0.0f, 0.0f,1.0f);
		if (input->GetKeyTrigger(VK_RETURN) || input->GetButtonTrigger(XINPUT_A))
		{
			state = 1;
		}
		break;
	case 1: cursol->SetPos(-300.0f, 50.0f + cursol_move, 0.0f);
			close->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			g_Sound.SetVolBGM(sound_cursol[0]->Update(input));
			break;
	case 2: cursol->SetPos(-300.0f, -200.0f + cursol_move, 0.0f);
			close->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			g_Sound.SetVolSE(sound_cursol[1]->Update(input));
			break;
	}
}

