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

	state = 0;
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

// �V�[���̃A�b�v�f�[�g
void TitleScene::Update() {
	// ���S�\�����ɓǂݍ���
	if (state == 0) {
		// ��
		//playSE();

		// �^�C�g���w�i====================
		title_bg = new Object;
		title_bg->Init(textureManager, L"asset/title/title 2_000.png");
		title_bg->SetPos(0.0f, 0.0f, 0.0f);         // �ʒu��ݒ�
		title_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // �傫����ݒ�

		// �^�C�g����=======================
		title_name = new Object;
		title_name->Init(textureManager, L"asset/title.png");
		title_name->SetPos(0.0f, 200.0f, 1.0f);       // �ʒu��ݒ�
		title_name->SetSize(993.0f, 315.0f, 0.0f);  // �傫����ݒ�

		//// �{�^���ݒu
		//for (int i = 0; i < 3; i++) {
		//    button[i] = std::make_unique<Object>();
		//    button[i]->Init(textureManager,L"asset/button");
		//    button[i]->SetPos((i * 100.0f) - 300.0f, 0.0f, 0.0f);
		//    button[i]->SetSize(100.0f,100.0f,0.0f);
		//}


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

		logo->SetColor(1.0f, 1.0f, 1.0f, logo->GetColor().w - 0.01f);
		if (logo->GetColor().w <= 0) {
			state = 1;
		}
	}
	else if (state == 1) {
		input.Update();  // �L�[���͂̔���
		if (input.GetKeyRelease(VK_RETURN)){
			SceneManager::ChangeScene(SceneManager::SELECT);  // �V�[����GAME�ֈڍs
		}

		// �ꉞ�A�j���[�V�����Ȃ邯�Ǐd������
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
	framecount++;
}

// �e�V�[���̕`��
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