#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int setscore, int setMscore, int settime) : Score(setscore), Mscore(setMscore), timescore(settime) {
	textureManager = new TextureManager(g_pDevice);

	result_bg = std::make_unique<Object>();
	result_bg->Init(textureManager, L"asset/title/title 2_000.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);         // �ʒu��ݒ�
	result_bg->SetSize(1920.0f, 1080.0f, 0.0f);  // �傫����ݒ�

	board = std::make_unique<Object>();
	board->Init(textureManager, L"asset/UI/result.png");
	board->SetPos(400.0f, 0.0f, 0.0f);         // �ʒu��ݒ�
	board->SetSize(1000.0f, 1000.0f, 0.0f);	// �傫����ݒ�

	sensuikan = std::make_unique<Object>();
	sensuikan->Init(textureManager, L"asset/UI/sensuikan.png");
	sensuikan->SetPos(-400.0f, 0.0f, 0.0f);         // �ʒu��ݒ�
	sensuikan->SetSize(800.0f, 800.0f, 0.0f);  // �傫����ݒ�

	button = std::make_unique<Object>();
	button->Init(textureManager, L"asset/UI/Abutton.png");
	button->SetPos(800.0f, -450.0f, 0.0f);         // �ʒu��ݒ�
	button->SetSize(100.0f, 100.0f, 0.0f);  // �傫����ݒ�

	for (int i = 0; i < 3; i++) {
		mendako.emplace_back(std::make_unique<Object>());
		mendako[i]->Init(textureManager, L"asset/UI/mendako2.png");
		mendako[i]->SetPos((i * 185.0f) + 215.0f, -98.5f, 0.0f);         // �ʒu��ݒ�
		mendako[i]->SetSize(175.0f, 175.0f, 0.0f);  // �傫����ݒ�
	}
	mendako[1]->SetPos(402.0f, -98.5f, 0.0f);


	for (int i = 0; i < 5; i++) {
		// UI�̐���
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/UI/num.png", 10, 1);	// ���̉摜���g�p
		scoreNum.back()->SetPos((i * 60.0f) + 380.0f, -250.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);

		timeNum.emplace_back(std::make_unique<Object>());
		timeNum.back()->Init(textureManager, L"asset/UI/num.png", 10, 1);	// ���̉摜���g�p
		timeNum.back()->SetPos((i * 60.0f) + 380.0f, 60.0f, 0.0f);
		timeNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		timeNum.back()->SetUV(0, 0);
	}
	// ���O�ɓǂݍ���
	for (int i = 0; i < 300; i++) {
		if (i % 5 == 0) {
			std::wstring texturePath = L"asset/title/title 2_";
			std::wstring tmp = L"000" + std::to_wstring(i);	// 3���ɒ���   
			tmp = tmp.substr(tmp.size() - 3);  // �Ō��3���݂̂��g�p
			texturePath += tmp;
			texturePath += L".png";
			result_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
	Mscore = 3;
	tempScore = Score;
}

ResultScene::~ResultScene() {
	delete textureManager;
}

void ResultScene::Update() {
	input.Update();

	if (state == 0) {
		// �����������ŉ�
		for (int i = 0; i < 5; i++) {
			scoreNum[i]->SetUV(rand() % 10, 0);
		}
		if (framecount == 100) {
			state = 1;          // �X�R�A�m��ֈڍs
			revealIndex = 0;    // ���̕\���J�n�ʒu
			scoreFixCounter = 0; // �X�R�A�m��p�̐V�����J�E���^�[
		}
	}
	else if (state == 1) {
		// �����E���珇��1���Œ�
		if (scoreFixCounter % 8 == 0 && revealIndex < static_cast<int>(scoreNum.size())) {
			int digit = tempScore % 10;  // �E�[�̌����擾
			tempScore /= 10;             // ���̌���
			scoreNum[scoreNum.size() - 1 - revealIndex]->SetUV(digit, 0);
			revealIndex++;
		}

		// �m�肵�����͌Œ肵�A���m��̌��͈������������_���\��
		for (int i = 0; i < static_cast<int>(scoreNum.size()) - revealIndex; i++) {
			scoreNum[i]->SetUV(rand() % 10, 0);
		}

		// �S���m���A���̏�Ԃ�
		if (revealIndex >= static_cast<int>(scoreNum.size())) {
			state = 2;
		}

		scoreFixCounter++;  // �m�菈���̃J�E���g��i�߂�
	}


	// �A�j���[�V����
	BgAnimation();
	SensuikanAnimation();

	if (input.GetKeyTrigger(VK_1) || input.GetButtonTrigger(VK_A)) {
		SceneManager::ChangeScene(SceneManager::SELECT);
	}
	framecount++;
	framecount = (framecount + 1) % 3600;
}

void ResultScene::Draw() {
	result_bg->Draw();
	board->Draw();
	sensuikan->Draw();
	button->Draw();
	for (int i = 0; i < Mscore; i++) {
		mendako[i]->Draw();
	}
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
	for (auto& obj : timeNum) {
		obj->Draw();
	}
}

void ResultScene::BgAnimation() {
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
			result_bg->SetTexture(textureManager, texturePath.c_str());
		}
	}
}

void ResultScene::SensuikanAnimation() {
	// �����ʒu
	DirectX::XMFLOAT3 initialPos(-400.0f, 0.0f, 0.0f);

	// X����Y���ɃT�C���g�ŗh���������
	float offsetX = amplitude * sin(framecount * frequency + noise);
	float offsetY = amplitude * 0.5f * sin(framecount * frequency * 1.2f);

	// �ʒu��ݒ�
	sensuikan->SetPos(initialPos.x + offsetX, initialPos.y + offsetY, initialPos.z);
}