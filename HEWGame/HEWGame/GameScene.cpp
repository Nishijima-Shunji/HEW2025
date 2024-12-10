#include "GameScene.h"
#include "Game.h"
#include <algorithm>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

// textureMapping�̏�����
	//�}�b�v����I�u�W�F�N�g�𐶐�����ۂɎQ�Ƃ���L�[
static std::unordered_map<int, std::wstring> textureMapping = {
	{1, L"asset/wall.png"},		//��
	{2, L"asset/player.png"},	//�v���C���[
	{3, L"asset/map_0.png"},	//���C�g
	{4, L"asset/enemy.png"}		//�G
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

	light->Update(WidthMAX, HeightMAX, maplist);
	//maplist = light->MapUpdate(maplist);

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

	// �}�b�v�f�[�^��CSV����ǂݍ���
	maplist = Loadmap("Data/TestData.csv");
	mapdata.resize(maplist.size()); // �O���̃x�N�g�������T�C�Y

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // �e�s�����T�C�Y
	  //���f�[�^�����Ă�
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != 0) {
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

std::unique_ptr<Object> GameScene::CreateObject(int objectType, TextureManager* textureManager) {
	std::unique_ptr<Object> obj;

	//�I�u�W�F�N�g�𐶐�
	switch (objectType) {
	case 1: obj = std::make_unique<Wall>(); break;
	case 2: obj = std::make_unique<Player>(); break;
	case 3: obj = std::make_unique<Light>(); break;
	case 4: obj = std::make_unique<Enemy>(); break;
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

void GameScene::GetMapSize()
{
	//���݃}�b�v�̍ő卂��
	for (int i = 0; i < 18; i++)
	{
		if (maplist[i][0] == 1)
		{
			HeightMAX++;
		}
	}
	//���݃}�b�v�̍ő剡��
	for (int j = 0; j < 32; j++)
	{
		if (maplist[0][j] == 1)
		{
			WidthMAX++;
		}
	}
}