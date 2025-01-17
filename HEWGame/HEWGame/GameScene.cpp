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

// textureMapping�̏�����
	//�}�b�v����I�u�W�F�N�g�𐶐�����ۂɎQ�Ƃ���L�[
static std::unordered_map<int, std::wstring> textureMapping = {
	{0, L"asset/S_Water.png"},		//��
	{1, L"asset/S_Wall.png"},		//��
	{2, L"asset/survivor3.png"},	//�v���C���[
	{3, L"asset/shake1.png"},		//�G
	{4, L"asset/S_Goal.png"},		//�S�[��
	{5, L"asset/mendako.png"},	//�����_�R
	{6, L"asset/mirror_fish.png"},	//����
	{7, L"asset/mirror_fish.png"},	//����
	{8, L"asset/S_trap.png"},		//�g���b�v
	{9, L"asset/S_Kairyu.png"},		//�C��
	{10, L"asset/S_Kairyu.png"},		//�C��
	{11, L"asset/S_hasi.png"},		//�}�b�v�[
	{15, L"asset/demonfish1.png"},	//�I�j�L����
	{16, L"asset/Lightfish1.png"},		//�A���R�E
	{19, L"asset/S_Light.png"},		//���C�g
	{20, L"asset/S_Lumine.png"}		//���}�X
};

GameScene::GameScene(int stage) {
	textureManager = new TextureManager(g_pDevice);
	// �X�e�[�W�I���őI�񂾔ԍ��̃}�b�v�f�[�^�����[�h
	LoadMapData(stage);


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
						float x = j * 30.0f - 500.0f;	// x���W		�� * Object�̑傫�� * �I�t�Z�b�g		���J��������΃I�t�Z�b�g�v��Ȃ�����
						float y = i * -30.0f + 280.0f;	// y���W		�s * Object�̑傫�� * �I�t�Z�b�g

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
		// �X�R�A�����U���g�ɓn���Ĉړ�
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

	std::string stageStr = std::to_string(stage);  // int �𕶎���ɕϊ�
	std::wstring mapPath = L"Data/MAP_STAGE" + std::wstring(stageStr.begin(), stageStr.end()) + L".csv";
	//std::wstring mapPath = L"Data/TestData.csv";

	maplist = Loadmap(mapPath.c_str());

	mapdata.resize(maplist.size()); // �O���̃x�N�g�������T�C�Y

	for (int i = 0; i < maplist.size(); ++i) {
		mapdata[i].resize(maplist[i].size()); // �e�s�����T�C�Y
		//���f�[�^�����Ă�
		for (int j = 0; j < maplist[i].size(); ++j) {
			int objectType = maplist[i][j];
			if (objectType != -1 && (objectType == 1 || objectType == 4 || objectType == 11 || objectType == 19 || objectType == 20)) {
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
			else if (objectType != -1) {
				auto obj = CreateObject(objectType, textureManager); // �I�u�W�F�N�g����
				if (obj) {
					float x = j * 30.0f - 500.0f; // x���W		�� * Object�̑傫�� * �I�t�Z�b�g
					float y = i * -30.0f + 280.0f; // y���W		�s * Object�̑傫�� * �I�t�Z�b�g

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
	//�I�u�W�F�N�g�𐶐�
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

	//textureMapping�ɐݒ肵���p�X��T��
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