#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()��srand()�̂���
#include <ctime>    // time()�̂���

TitleScene::TitleScene() {
	textureManager = new TextureManager(g_pDevice);

	// ���S�\��
	logo = std::make_unique<Object>();
	logo->Init(textureManager, L"asset/logo.png");
	logo->SetPos(0.0f, 0.0f, 0.0f);
	logo->SetSize(800.0f, 800.0f, 0.0f);
	logo->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �^�C�g���I�u�W�F�N�g=============
	//InitTitleObjects(10);  // �����_���Ȉʒu��10�̃I�u�W�F�N�g��������
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
	srand(static_cast<unsigned>(time(0)));  // �����_���������̂��߂̃V�[�h

	for (int i = 0; i < count; ++i) {
		Object* obj = new Object;
		obj->Init(textureManager, L"asset/Bg/konbu.png", 8, 4);
		float x = static_cast<float>((rand() % 1000) - 500);  // �����_����x�ʒu
		float y = static_cast<float>((rand() % 500) - 400);   // �����_����y�ʒu
		// y�̒l���������قǑ傫������
		float sizeFactor_Bg = 1.0f + (25.0f - y) / 25.0f;  // y���������ق�sizeFactor���傫���Ȃ�
		float width_konbu = 10.0f * sizeFactor_Bg;//���z�̕�
		float height_konbu = 10.0f * sizeFactor_Bg;//����
		obj->SetPos(x, y, 1.0f);  // �ʒu��ݒ�
		obj->SetSize(width_konbu, height_konbu, 0.0f);  // �傫����ݒ�
		obj->SetAngle(0.0f);  // �p�x��ݒ�
		obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // �F��ݒ�
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
		// ���z
		/*	for (auto obj : title_Ob) {
				obj->Draw();
			}*/
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
		}
	}
}

void TitleScene::InitAnimation() {
	// SE�Đ�
		//playSE();

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
		window[i]->Init(textureManager, L"asset/window.png");
		window[i]->SetPos((i * 375.0f) - 375.0f, -145.0f, 0.0f);
		window[i]->SetSize(200.0f, 200.0f, 0.0f);

		icon.emplace_back(std::make_unique<Object>());
		icon[i]->SetPos((i * 375.0f) - 375.0f, -145.0f, 0.0f);
		icon[i]->SetSize(150.0f, 150.0f, 0.0f);
	}
	button[0]->Init(textureManager, L"asset/OPTION.png");
	button[1]->Init(textureManager, L"asset/START.png");
	button[2]->Init(textureManager, L"asset/EXIT.png");
	icon[0]->Init(textureManager, L"asset/haguruma.png");
	icon[1]->Init(textureManager, L"asset/mendako_icon.png");
	icon[2]->Init(textureManager, L"asset/batten.png");

	// light�\��
	light = std::make_unique<Object>();
	light->Init(textureManager, L"asset/FrashLight.png");
	light->SetPos(-375.0f, -350.0f, 0.0f);
	light->SetSize(500.0f, 500.0f, 0.0f);
	light->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �ݒ�E�B���h�E
	setting = std::make_unique<Object>();
	setting->Init(textureManager, L"asset/sound_UI.png");
	setting->SetPos(0.0f, 0.0f, 0.0f);
	setting->SetSize(600.0f, 600.0f, 0.0f);

	sound_cursol = std::make_unique<SoundCursol>();
	sound_cursol->Init(textureManager, L"asset/sound_UI.png");
	sound_cursol->SetPos(0.0f, 0.0f, 0.0f);
	sound_cursol->SetSize(600.0f, 600.0f, 0.0f);

	cursol = std::make_unique<Cursol>();
	cursol->Init(textureManager, L"asset/cursol.png");
	cursol->SetPos(0.0f, 0.0f, 0.0f);
	cursol->SetSize(100.0f, 100.0f, 0.0f);

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


	// ���X�Ƀ��S�������Ă���
	logo->SetColor(1.0f, 1.0f, 1.0f, logo->GetColor().w - 0.01f);
	if (logo->GetColor().w <= 0) {
		state = 1;
	}
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
		if (input->GetKeyTrigger(VK_LEFT)) {
			if (nowButton > 1) {
				selectButton--;
			}
		}
		if (input->GetKeyTrigger(VK_RIGHT)) {
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

	// �V�[���̐؂�ւ������邩���ԍŌ�(�r���ɂ���ƃV�[���̒m��ւ���ɏ�����)
	if (input->GetKeyTrigger(VK_RETURN)) {
		switch (nowButton) {
		case 1: state = 2; break;
		case 2: SceneManager::ChangeScene(SceneManager::SELECT); break;
		case 3: break;
		}
	}
}

void TitleScene::OptionSelect(Input* input) {
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
	switch (select) {
	case 0:
		cursol->SetPos(100.0f, 100.0f, 0.0f);
		if (input->GetKeyTrigger(VK_RETURN))
		{
			state = 1;
		}
		break;
	case 1: cursol->SetPos(-100.0f, 0.0f, 0.0f); break;
	case 2: cursol->SetPos(-100.0f, -100.0f, 0.0f); break;
	}
}
