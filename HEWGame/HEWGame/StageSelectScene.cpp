#include "StageSelectScene.h"
#include "Game.h"

StageSelectScene::StageSelectScene() {
	textureManager = new TextureManager(g_pDevice);

	select_bg = std::make_unique<Object>();
	select_bg->Init(textureManager, L"asset/stage_select2/stage_select 2_000.png", 8, 4);
	select_bg->SetPos(0.0f, 0.0f, 0.0f);			//�ʒu��ݒ�
	select_bg->SetSize(1920.0f, 1080.0f, 0.0f);		//�傫����ݒ�
	select_bg->SetAngle(0.0f);						//�p�x��ݒ�
	select_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�
	// ���O�ɓǂݍ���
	for (int i = 0; i < 300; i++) {
		if (i % 5 == 0) {
			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
			std::wstring pathindex = L"000" + std::to_wstring(i);	// 3���ɒ���   
			pathindex = pathindex.substr(pathindex.size() - 3);  // �Ō��3���݂̂��g�p
			texturePath += pathindex;
			texturePath += L".png";
			select_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
	// �X�e�[�W�̃A�C�R���摜�𐶐�
	for (int i = 0; i < 8; i++) {
		// ����
		stageicon.emplace_back(std::make_unique<Object>());
		// �C���f�b�N�X���̃p�X�w��
		std::wstring texturePath = L"asset/stage_icon/";
		texturePath += std::to_wstring(i + 1);
		texturePath += L".png";
		stageicon[i]->Init(textureManager, texturePath.c_str());
		stageicon[i]->SetPos(i * 800.0f + 0.0f, -170.0f, 0.0f);
		stageicon[i]->SetSize(400.0f, 400.0f, 0.0f);
	}
	sensuikan = std::make_unique<Object>();
	sensuikan->Init(textureManager, L"asset/sensuikan.png", 1, 1);
	sensuikan->SetPos(0.0f, -400.0f, 0.0f);			//�ʒu��ݒ�
	sensuikan->SetSize(310.25f, 250.0f, 0.0f);		//�傫����ݒ�
}

StageSelectScene::~StageSelectScene() {
	delete textureManager;
}

void StageSelectScene::Update() {
	input.Update();

	if (nowStage != nextStage) {
		if (nowStage < nextStage) {
			for (auto& obj : stageicon) {
				DirectX::XMFLOAT3 pos = obj->GetPos();
				pos.x -= 8.0f;
				obj->SetPos(pos.x, pos.y, pos.z);
			}
		}
		else
		{
			for (auto& obj : stageicon) {
				DirectX::XMFLOAT3 pos = obj->GetPos();
				pos.x += 8.0f;
				obj->SetPos(pos.x, pos.y, pos.z);
			}
		}
	}

	if (stageicon[nextStage - 1]->GetPos().x == 0.0f) {
		nowStage = nextStage;
	}

	// �X�e�[�W�ړ�
	if (input.GetKeyTrigger(VK_LEFT) && nowStage > 1) {
		nextStage -= 1;
	}
	if (input.GetKeyTrigger(VK_RIGHT) && nowStage < 8) {
		nextStage += 1;
	}
	if (input.GetKeyTrigger(VK_RETURN) && nowStage == nextStage) {
		// ���݈ʒu�̔ԍ��X�e�[�W�ŃQ�[���V�[���ǂݍ���
		SceneManager::ChangeScene(SceneManager::GAME, nowStage);
	}
	// �ꉞ�A�j���[�V�����Ȃ邯�Ǐd������
	if (framecount % 1 == 0) {
		int textureIndex = (framecount / 1) % 300;  // 0 ���� 299 �͈̔͂Ƀ��}�b�v
		// ����5�t���[�����̃A�j���[�V������
		if (textureIndex % 5 == 0) {
			// ���݂̃A�j���[�V�����ɑΉ�����p�X�ɑg�ݍ��킹��
			std::wstring texturePath = L"asset/stage_select2/stage_select 2_";
			std::wstring pathindex = L"000" + std::to_wstring(textureIndex);	// 3���ɒ���   
			pathindex = pathindex.substr(pathindex.size() - 3);  // �Ō��3���݂̂��g�p
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
}