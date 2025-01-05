#include "GameScene.h"
#include "Game.h"
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

// textureMapping�̏�����
	//�}�b�v����I�u�W�F�N�g�𐶐�����ۂɎQ�Ƃ���L�[
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},	//��
	{1, L"asset/S_Wall.png"},	//��
	{2, L"asset/S_Player.png"},	//�v���C���[
	{3, L"asset/S_Light.png"},	//���C�g
	{4, L"asset/S_Enemy.png"},	//�G
	{5, L"asset/S_Lumine.png"}	//����
};

GameScene::GameScene() {
	textureManager = new TextureManager(g_pDevice);
	// �}�b�v�f�[�^�����[�h
	LoadMapData();
}

GameScene::~GameScene() {
	// mapdata�̃��\�[�X�����
	for (auto& row : mapdata) {
		for (auto& obj : row) {
			obj.reset(); // unique_ptr �̃��\�[�X���
		}
	}
	mapdata.clear(); // �����I�Ƀx�N�g�����N���A

	// TextureManager�����
	delete textureManager;
}

void GameScene::Update() {
	input.Update();

	//�Â��}�b�v�f�[�^�̕ۑ�
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

	//�}�b�v�f�[�^�̍X�V
	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // �e�s�����T�C�Y
		for (int j = 0; j < maplist[i].size(); ++j) {

			//�Â��}�b�v�f�[�^�Ɣ�r
			int OldObject = oldlist[i][j];
			int NewObject = maplist[i][j];

			//�}�b�v�f�[�^���ω����Ă���Ȃ�
			if (NewObject != OldObject)
			{
				//�Â��I�u�W�F�N�g���폜
				std::cout << "�폜" << std::endl;
				mapdata[i][j] = CreateObject(NewObject, textureManager);

				// ���d�������������Fif���̒��ɓ���ĕω��������ɂ����炿����ƌy���Ȃ���
				int objectType = maplist[i][j];
				if (objectType != -1) {
					auto obj = CreateObject(objectType, textureManager); // Factory�֐��ŃI�u�W�F�N�g����
					if (obj) {
						float x = j * 30.0f - 500.0f; // x���W		�� * Object�̑傫�� * �I�t�Z�b�g
						float y = i * -30.0f + 280.0f; // y���W		�s * Object�̑傫�� * �I�t�Z�b�g

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

	// �}�b�v�f�[�^��CSV����ǂݍ���
	maplist = Loadmap("Data/TestData.csv");
	mapdata.resize(maplist.size()); // �O���̃x�N�g�������T�C�Y

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // �e�s�����T�C�Y
		//���f�[�^�����Ă�
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != -1 && (objectType == 1 || objectType == 3)) {
				auto obj = CreateObject(objectType, textureManager); // �I�u�W�F�N�g����
				if (obj) {
					float x = j * 30.0f - 500.0f; // x���W		�� * Object�̑傫�� * �I�t�Z�b�g
					float y = i * -30.0f + 280.0f; // y���W		�s * Object�̑傫�� * �I�t�Z�b�g

					obj->SetPos(x, y, 0.0f);
					obj->SetSize(30.0f, 30.0f, 0.0f);
					obj->SetAngle(0.0f);
					obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);

					mapdata[i][j] = std::move(obj);
				}
			}
			else if (objectType != -1 && (objectType == 2 || objectType == 4)) {
				auto obj = CreateObject(objectType, textureManager); // �I�u�W�F�N�g����
				if (obj) {
					float x = j * 30.0f - 500.0f; // x���W		�� * Object�̑傫�� * �I�t�Z�b�g
					float y = i * -30.0f + 280.0f; // y���W		�s * Object�̑傫�� * �I�t�Z�b�g

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

	//�I�u�W�F�N�g�𐶐�
	switch (objectType) {
	case 0: obj = std::make_unique<Object>(); break;
	case 1: obj = std::make_unique<Wall>(); break;
	case 2: obj = std::make_unique<Player>(); break;
	case 3: obj = std::make_unique<Light>(); break;
	case 4: obj = std::make_unique<Enemy>(); break;
	case 5: obj = std::make_unique<Object>(); break;
	default: return nullptr;
	}

	//textureMapping�ɐݒ肵���p�X��T��
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