#include "GameScene.h"
#include "GameScene.h"
#include "Game.h"
#include <algorithm>

//��
GameScene::GameScene() {
	textureManager = new TextureManager(g_pDevice);

	game_bg_list.resize(1000);  // �I�u�W�F�N�g��1000��������

	for (int i = 0; i < 1000; ++i) {
		game_bg_list[i] = new Object;  // �I�u�W�F�N�g����
		printf("game_bg[%d] ����\n", i);
		game_bg_list[i]->Init(textureManager, L"asset/Game_test.png", 8, 4);
		game_bg_list[i]->SetPos(0.0f + i * 10, 0.0f, 0.0f);  // �ʒu�����������炷��
		game_bg_list[i]->SetSize(300.0f, 300.0f, 0.0f);  // �傫����ݒ�
		game_bg_list[i]->SetAngle(0.0f);  // �p�x��ݒ�
		game_bg_list[i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // �F��ݒ�
	}
	//�}�b�v�ǂݍ���
	LoadMapData();
	for (int i = 0; i < maplist.size(); ++i) {
		if (maplist[i] != 0) {
			switch (maplist[i]) {
			case 0: mapdata[i]->Init(textureManager, L"asset/map_0.png", 8, 4); break;
			case 1: mapdata[i]->Init(textureManager, L"asset/map_1.png", 8, 4); break;
			case 2: mapdata[i]->Init(textureManager, L"asset/map_2.png", 8, 4); break;
			}
			mapdata[i]->SetPos((i % 10) * 20.0f - 100.0f, ((i / 10) * -20.0f) + 100.0f, 0.0f);	//�ʒu��ݒ�
			mapdata[i]->SetSize(20.0f, 20.0f, 0.0f);	//�傫����ݒ�
			mapdata[i]->SetAngle(0.0f);	//�p�x��ݒ�
			mapdata[i]->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�
		}
	}
}

GameScene::~GameScene() {
	for (int i = 0; i < 1000; ++i) {
		game_bg_list[i]->Uninit();			//�^�C�g�����I��
		printf("game_bg ���\n");
		delete game_bg_list[i];
	}
	delete textureManager;					//�e�N�X�`���}�l�[�W���[�̍폜
}

void GameScene::Update() {
	input.Update();
	if (input.GetKeyTrigger(VK_3)) {
		SceneManager::ChangeScene(SceneManager::RESULT);
	}
}

void GameScene::Draw() {
	for (int i = 0; i < 1000; i++) {
		game_bg_list[i]->Draw();
	}
	for (int i = 0; i < mapdata.size(); i++) {
		mapdata[i]->Draw();
	}
}

void GameScene::LoadMapData() {
	mapdata.resize(0);

	maplist = Loadmap("Data/TestData.csv");		//�}�b�v�̏����擾
	mapval = maplist.size();

	/*Object* obj[3] = { nullptr };
	obj[0] = map_0;
	obj[1] = map_1;
	obj[2] = map_2;*/

	for (int i = 0; i < mapval; i++) {
		mapdata.emplace_back(std::make_unique<Object>());	//�}�b�v�̃I�u�W�F�N�g������ǉ�
	}

	//for (int i = 0; i < mapval; i++) {
	//	for (int j = 0; j < 70; j++) {
	//		int dataValue = maplist[j];
	//		if (dataValue != 0 && dataValue < 3) {  // 0�ȊO���͈͓��̃f�[�^
	//			mapdata[i] = std::make_unique<Object>(*obj[dataValue]);
	//		}
	//	}
	//}
}