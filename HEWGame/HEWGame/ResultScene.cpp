#include "ResultScene.h"
#include "Game.h"
#include "camera.h"

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
		mendako[i]->Init(textureManager, L"asset/UI/mendako2-02.png");
		mendako[i]->SetPos((i * 185.0f) + 215.0f, -97.0f, 0.0f);         // �ʒu��ݒ�
		mendako[i]->SetSize(175.0f, 175.0f, 0.0f);  // �傫����ݒ�
	}
	mendako[1]->SetPos(402.0f, -97.0f, 0.0f);

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
	//timeNum[2]->SetTexture(textureManager,L"asset/UI/:.png");

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
	// �X�R�A���R�s�[
	tempScore = Score;
	timescore = 70000;
	temptime = timescore / 1000;

	g_Camera.SetCamera(0.0f, 0.0f, 1.0f);
}

ResultScene::~ResultScene() {
	delete textureManager;
}

void ResultScene::Update() {
	input.Update();

	// =====�����������_���ɕς���=====
	if (state == 0) {
		// �X�R�A�̖��m��A�j���[�V����
		randomNum();
		TimeConfirmed();
	}
	// =====�����������_���ɕς���=====
	else if (state == 1) {
		// �����_�R�̎擾���\��
		MendakoConfirmed();
		// �X�R�A�̌Œ�
		NumConfirmed();

		// �����_�R�̃A�j���[�V�����p
		animtime++;
		// �m�菈���̃J�E���g��i�߂�
		scoreFixCounter++;  
	}
	// =====�{�^�����͎�t=====
	else if (state == 2) {
		if (input.GetKeyTrigger(VK_SPACE) || input.GetButtonTrigger(XINPUT_A)) {
			state = 3;
		}
	}
	// =====�{�^�������ꂽ��̃A�j���[�V����=====
	else if (state == 3) {
		// �V�[���؂�ւ��O�̃A�j���[�V����
		SensuikanExit();
	}

	// �w�i�A�j���[�V����
	BgAnimation();
	if (state < 3) {
		SensuikanAnimation();
	}


	framecount++;
	framecount = (framecount + 1) % 3600;
}

void ResultScene::Draw() {
	result_bg->Draw();
	board->Draw();
	sensuikan->Draw();
	if (mendakoSet > 1) {
		button->Draw();
	}
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
	for (auto& obj : timeNum) {
		obj->Draw();
	}
	for (int i = 0; i < Mscore; i++) {
		if (mendakoSet >= i && state > 0) {
			mendako[i]->Draw();
		}
	}
}

void ResultScene::TimeConfirmed() {
	// ���ƕb���v�Z
	int minutes = temptime / 60;  // �����v�Z
	int seconds = temptime % 60; // �b���v�Z

	// ���ƕb�̊e���𕪉�
	int displayTime[4] = {
		minutes / 10,  // ���̏\�̈�
		minutes % 10,  // ���̈�̈�
		seconds / 10,  // �b�̏\�̈�
		seconds % 10   // �b�̈�̈�
	};

	// ���̕\�� (timeNum[0] �� timeNum[1])
	timeNum[0]->SetUV(displayTime[0], 0); // ���̏\�̈�
	timeNum[1]->SetUV(displayTime[1], 0); // ���̈�̈�

	// �b�̕\�� (timeNum[3] �� timeNum[4])
	timeNum[3]->SetUV(displayTime[2], 0); // �b�̏\�̈�
	timeNum[4]->SetUV(displayTime[3], 0); // �b�̈�̈�
}

void ResultScene::randomNum() {
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

void ResultScene::NumConfirmed() {
	// �����E���珇��1���Œ�
	if (scoreFixCounter > 0 + (Mscore * 50)) {
		if (scoreFixCounter % 8 == 0 && revealIndex < static_cast<int>(scoreNum.size())) {
			int digit = tempScore % 10;  // �E�[�̌����擾
			tempScore /= 10;             // ���̌���
			scoreNum[scoreNum.size() - 1 - revealIndex]->SetUV(digit, 0);
			revealIndex++;
		}
	}

	// �m�肵�����͌Œ肵�A���m��̌��͈������������_���\��
	for (int i = 0; i < static_cast<int>(scoreNum.size()) - revealIndex; i++) {
		scoreNum[i]->SetUV(rand() % 10, 0);
	}
}

void ResultScene::MendakoConfirmed() {
	DirectX::XMFLOAT3 offsetSize = { 2000.0f, 2000.0f, 0.0f };
	if (mendakoSet < mendako.size()) {
		mendako[mendakoSet]->SetSize(offsetSize.x - animtime * 100, offsetSize.y - animtime * 100, offsetSize.z);
		if (mendako[mendakoSet]->GetSize().x < 175.0f) {
			mendako[mendakoSet]->SetSize(175.0f, 175.0f, 0.0f);
			mendakoSet++;
			animtime = 0;
		}
	}
	// �S���m���A���̏�Ԃ�
	if (revealIndex >= static_cast<int>(scoreNum.size()) && mendakoSet == 3) {
		state = 2;
	}
}

void ResultScene::SensuikanExit() {
	// �����͈ȊO���E�֑���
	float speed = 80.0f;
	board->SetPos(board->GetPos().x + speed, board->GetPos().y, board->GetPos().z);
	button->SetPos(button->GetPos().x + speed, button->GetPos().y, button->GetPos().z);
	for (int i = 0; i < mendako.size(); i++) {
		mendako[i]->SetPos(mendako[i]->GetPos().x + speed, mendako[i]->GetPos().y, mendako[i]->GetPos().z);
	}
	for (int i = 0; i < scoreNum.size(); i++) {
		timeNum[i]->SetPos(timeNum[i]->GetPos().x + speed, timeNum[i]->GetPos().y, timeNum[i]->GetPos().z);
		scoreNum[i]->SetPos(scoreNum[i]->GetPos().x + speed, scoreNum[i]->GetPos().y, scoreNum[i]->GetPos().z);
	}

	// �����͂𕂏コ����
	// ���݈ʒu���擾
	DirectX::XMFLOAT3 tmpPos = sensuikan->GetPos();

	// �����x��K�p���đ��x�𑝉�
	velocityY += acceleration;

	// �ʒu���X�V
	sensuikan->SetPos(tmpPos.x, tmpPos.y + velocityY, tmpPos.z);

	// ��ʊO�`�F�b�N
	if (sensuikan->GetPos().y > 1000.0f) {
		SceneManager::ChangeScene(SceneManager::SELECT);
		velocityY = 0.0f;  // �V�[���ύX���ɑ��x�����Z�b�g
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