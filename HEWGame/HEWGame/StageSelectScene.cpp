#include "StageSelectScene.h"
#include "Game.h"
#include "camera.h"
#include "File.h"

StageSelectScene::StageSelectScene() {
	textureManager = new TextureManager(g_pDevice);

	g_Camera.SetCamera(0.0f,0.0f,1.0f);

	select_bg = std::make_unique<Object>();
	select_bg->Init(textureManager, L"asset/stage_select2/stage_select 2_000.png", 1, 1);
	select_bg->SetPos(0.0f, 0.0f, 0.0f);			//�ʒu��ݒ�
	select_bg->SetSize(1920.0f, 1080.0f, 0.0f);		//�傫����ݒ�
	select_bg->SetAngle(0.0f);						//�p�x��ݒ�
	select_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�

	load_bg = std::make_unique<Object>();
	load_bg->Init(textureManager, L"asset/loadbg.png", 1, 1);
	load_bg->SetPos(0.0f, 0.0f, 0.0f);			//�ʒu��ݒ�
	load_bg->SetSize(0.0f, 0.0f, 0.0f);			//�傫����ݒ�

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
	for (int i = 0; i < 60; i++) {
		//std::wstring texturePath = L"asset/stage_night_6fps/stage_hight_re_";
		std::wstring texturePath = L"asset/�R���| 1/�R���| 1_";
		std::wstring pathindex = L"000" + std::to_wstring(i);	// 3���ɒ���   
		pathindex = pathindex.substr(pathindex.size() - 3);  // �Ō��3���݂̂��g�p
		texturePath += pathindex;
		//texturePath += L".png";
		texturePath += L".jpg";
		select_bg->SetTexture(textureManager, texturePath.c_str());
	}
	// �X�e�[�W�̃A�C�R���摜�𐶐�
	for (int i = 0; i < 4; i++) {
		// ����
		stageicon.emplace_back(std::make_unique<Object>());
		// �C���f�b�N�X���̃p�X�w��
		std::wstring texturePath = L"asset/stage_icon/";
		texturePath += std::to_wstring(i + 1);
		texturePath += L".png";

		stageicon[i]->Init(textureManager, texturePath.c_str());
		stageicon[i]->SetPos(i * 475.0f - 700.0f, -230.0f, 0.0f);
		stageicon[i]->SetSize(230.0f, 230.0f, 0.0f);
	}
	sensuikan = std::make_unique<Object>();
	sensuikan->Init(textureManager, L"asset/sensuikan.png", 1, 1);
	sensuikan->SetPos(-700.0f, -400.0f, 0.0f);		//�ʒu��ݒ�
	sensuikan->SetSize(200.0f, 200.0f, 0.0f);		//�傫����ݒ�

	loadstate = 0;

	//����
	rg[BUBBLE_X] = std::make_unique<RandomGene>(-960, 960);
	rg[BUBBLE_SPEED] = std::make_unique<RandomGene>(10.0f, 15.0f);
	rg[BUBBLE_SIZE] = std::make_unique<RandomGene>(10.0f, 15.0f);

	// ����
	Score_Bord = std::make_unique<Object>();
	Score_Bord->Init(textureManager, L"asset/UI/Lording.png", 1, 1);
	Score_Bord->SetPos(0.0f, -600.0f, 0.0f);
	Score_Bord->SetSize(158.0f, 88.9f, 0.0f);
	
	//�߂񂾂��̓ǂݍ���
	for (int stage = 1; stage < 9; stage++) {
		mendako[stage - 1] = LoadFile(stage);
	}

	Score_mendako.emplace_back(std::make_unique<Object>());
	Score_mendako[0]->Init(textureManager, L"asset/UI/mendako2-02.png", 1, 1);
	Score_mendako[0]->SetPos(-117.5f, -642.0f, 0.0f);
	Score_mendako[0]->SetSize(30.5f, 30.5f, 0.0f);

	Score_mendako.emplace_back(std::make_unique<Object>());
	Score_mendako[1]->Init(textureManager, L"asset/UI/mendako2-02.png", 1, 1);
	Score_mendako[1]->SetPos(2.5f, -642.0f, 0.0f);
	Score_mendako[1]->SetSize(30.5f, 30.5f, 0.0f);

	Score_mendako.emplace_back(std::make_unique<Object>());
	Score_mendako[2]->Init(textureManager, L"asset/UI/mendako2-02.png", 1, 1);
	Score_mendako[2]->SetPos(118.5f, -642.0f, 0.0f);
	Score_mendako[2]->SetSize(30.5f, 30.5f, 0.0f);
}

StageSelectScene::~StageSelectScene() {
	delete textureManager;
}

void StageSelectScene::Update() {
	input.Update();

	Select();

	Load();
	Move();
	BG_Animation();

	framecount++;
}

void StageSelectScene::Draw() {
	select_bg->Draw();
	for (auto& obj : stageicon) {
		obj->Draw();
	}
	sensuikan->Draw();
	Score_Bord->Draw();
	for (auto& obj : Score_mendako) {
		obj->Draw();
	}
	for (auto& obj : bubble) {
		obj->Draw();
	}

	// ��ԑO�ɂ��邩��Ō�
	if (loadstate > 0 && (loadstate == 1 || loadstate == 2)) {
		load_bg->Draw();
	}
}

void StageSelectScene::Move() {
	// ������ʒu���ړI�n����Ȃ��Ȃ�ړ�
	if (nowStage != nextStage) {
		move = true;
	}
	else {
		move = false;
	}
	if (move) {
		if (nowStage < nextStage) {
			DirectX::XMFLOAT3 pos = sensuikan->GetPos();
			pos.x += 10.0f;
			sensuikan->SetPos(pos.x, pos.y, pos.z);
			sensuikan->SetDirection(1);
		}
		else
		{
			DirectX::XMFLOAT3 pos = sensuikan->GetPos();
			pos.x -= 10.0f;
			sensuikan->SetPos(pos.x, pos.y, pos.z);
			sensuikan->SetDirection(0);
		}

		DirectX::XMFLOAT3 SB_pos = Score_Bord->GetPos(), SB_siz = Score_Bord->GetSize();
		if (SB_pos.y > -600.0f) {
			SB_pos.y -= 50.0f;
			SB_siz.x /= 1.1f;
			SB_siz.y /= 1.1f;
			Score_Bord->SetPos(SB_pos);
			Score_Bord->SetSize(SB_siz);
			int stage_mendako = 0;
			for (auto& obj : Score_mendako) {
				if (mendako[nowStage - 1] - stage_mendako < 1) {
					break;
				}
				DirectX::XMFLOAT3 SM_pos = obj->GetPos(), SM_siz = obj->GetSize();
				SM_pos.y -= 50.0f;
				SM_siz.x /= 1.1f;
				SM_siz.y /= 1.1f;
				obj->SetPos(SM_pos);
				obj->SetSize(SM_siz);
				stage_mendako++;
			}
		}
	}
	if (nextStage < 5) {
		// �ړI�n�ƍ��̈ʒu���������������Ȃ��~
		if (abs((stageicon[nextStage - 1]->GetPos().x - sensuikan->GetPos().x)) < 10.0f) {
			nowStage = nextStage;
		}
	}
	else if (nextStage > 4) {
		// �ړI�n�ƍ��̈ʒu���������������Ȃ��~
		if (abs((stageicon[nextStage - 5]->GetPos().x - sensuikan->GetPos().x)) < 10.0f) {
			nowStage = nextStage;
		}
	}

	if (nextStage == nowStage) {
		DirectX::XMFLOAT3 SB_pos = Score_Bord->GetPos(), SB_siz = Score_Bord->GetSize();
		if (SB_pos.y < 100.0f) {
			SB_pos.y += 50.0f;
			SB_siz.x *= 1.1f;
			SB_siz.y *= 1.1f;
			Score_Bord->SetPos(SB_pos);
			Score_Bord->SetSize(SB_siz);
			int stage_mendako = 0;
			for (auto& obj : Score_mendako) {
				if (mendako[nowStage - 1] - stage_mendako < 1) {
					break;
				}
				DirectX::XMFLOAT3 SM_pos = obj->GetPos(), SM_siz = obj->GetSize();
				SM_pos.y += 50.0f;
				SM_siz.x *= 1.1f;
				SM_siz.y *= 1.1f;
				obj->SetPos(SM_pos);
				obj->SetSize(SM_siz);
				stage_mendako++;
			}
		}
	}
}

void StageSelectScene::Load() {
	// ��ʐ؂�ւ�
	// �E�[�����[�ɍs�����Ƃ�
	if ((sensuikan->GetPos().x > 1000.0f && nextStage == 5 && loadstate == 0)
		|| (sensuikan->GetPos().x < -1000.0f && nextStage == 4 && loadstate == 0)) {
		loadstate = 1;
	}

	// �؂�ւ���
	if (loadstate == 1) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x += 60.0f;
		size.y += 60.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x > 2500.0f) {
			loadstate = 3;
		}
	}
	// ��ʖ߂�
	if (loadstate == 2) {
		DirectX::XMFLOAT3 size = load_bg->GetSize();
		size.x -= 60.0f;
		size.y -= 60.0f;
		load_bg->SetSize(size.x, size.y, size.z);
		if (size.x < -10.0f) {
			loadstate = 0;
		}
	}
	if (loadstate == 3) {
		int count = 0;
		for (auto& obj : stageicon) {
			std::wstring texturePath = L"asset/stage_icon/";
			if (nextStage == 5) {
				texturePath += std::to_wstring(count + 5);
			}
			else if (nextStage == 4) {
				texturePath += std::to_wstring(count + 1);
			}
			texturePath += L".png";
			obj->SetTexture(textureManager, texturePath.c_str());
			count++;
		}
		if (nextStage == 5) {
			sensuikan->SetPos(-1200.0f, -400.0f, 0.0f);
			state = 1;
		}
		else if (nextStage == 4) {
			sensuikan->SetPos(1200.0f, -400.0f, 0.0f);
			state = 0;
		}
		loadstate = 2;
	}

	//�@�Q�[���V�[���֐؂�ւ��̃A�j���[�V����
	if (loadstate == 5) {
		move = false;
		sensuikan->SetPos(sensuikan->GetPos().x, sensuikan->GetPos().y - 2.0f, 0.0f);
		if (framecount % (rand() % 5 + 2) == 0) {
			bubble.emplace_back(std::make_unique<Bubble>());
			bubble.back()->Init(textureManager, L"asset/bubble.PNG");
			bubble.back()->SetPos(rg[BUBBLE_X]->Int_generate(), -800.0f, 0.0f);
			float sizerandom = rg[BUBBLE_SIZE]->Float_generate() * framecount;
			bubble.back()->SetSize(sizerandom, sizerandom, 0.0f);
			bubble.back()->SetSpeed(rg[BUBBLE_SPEED]->Float_generate());
		}
		for (auto& obj : bubble) {
			obj->Update();
		}
		bubble.erase(std::remove_if(bubble.begin(), bubble.end(),
			[](const std::unique_ptr<Bubble>& bubble) { return bubble->GetPosY() > 800.0f; }),
			bubble.end());

		if (loadstate == 5) {
			if (framecount == 250) {
				// ���݈ʒu�̔ԍ��X�e�[�W�ŃQ�[���V�[���ǂݍ���
				SceneManager::ChangeScene(SceneManager::GAME, nowStage);
			}
		}
	}
}

void StageSelectScene::Select() {
	// �ړ�
	if (!move && loadstate == 0) {
		// �X�e�[�W�ړ�
		if ((input.GetKeyTrigger(VK_LEFT) || input.GetButtonPress(XINPUT_LEFT)) && nowStage > 1) {
			nextStage -= 1;
		}
		if ((input.GetKeyTrigger(VK_RIGHT) || input.GetButtonPress(XINPUT_RIGHT)) && nowStage < 4) {
			nextStage += 1;
		}
		// ����
		if ((input.GetKeyTrigger(VK_RETURN) || input.GetButtonPress(XINPUT_A)) && nowStage == nextStage) {
			loadstate = 5;
			framecount = 0;
		}
		if (input.GetButtonPress(XINPUT_B)) {
			SceneManager::ChangeScene(SceneManager::TITLE,1);
		}
	}
}

void StageSelectScene::BG_Animation() {
	// �ꉞ�A�j���[�V�����Ȃ邯�Ǐd�����邽��5�t���[�����Ƃ�
	if (state == 0) {

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
	}
	if (state == 1) {
		if (framecount % 5 == 0) {
			int textureIndex = (framecount / 5) % (60);  // 0 ���� 299 �͈̔͂Ƀ��}�b�v
			// ����5�t���[�����̃A�j���[�V������
				// ���݂̃A�j���[�V�����ɑΉ�����p�X�ɑg�ݍ��킹��
			//std::wstring texturePath = L"asset/stage_night_6fps/stage_hight_re_";
			std::wstring texturePath = L"asset/�R���| 1/�R���| 1_";
			std::wstring pathindex = L"000" + std::to_wstring(textureIndex);	// 3���ɒ���   
			pathindex = pathindex.substr(pathindex.size() - 3);  // �Ō��3���݂̂��g�p
			texturePath += pathindex;
			//texturePath += L".png";
			texturePath += L".jpg";
			select_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
}