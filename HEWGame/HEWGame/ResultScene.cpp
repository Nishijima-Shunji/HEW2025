#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int score) : score(score) {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result_test.png");
	result_bg->SetPos(0.0f, 0.0f, 0.0f);			//�ʒu��ݒ�
	result_bg->SetSize(300.0f, 300.0f, 0.0f);		//�傫����ݒ�
	result_bg->SetAngle(0.0f);						//�p�x��ݒ�
	result_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�

	for (int i = 0; i < 5; i++) {
		// UI�̐���
		scoreNum.emplace_back(std::make_unique<Object>());
		scoreNum.back()->Init(textureManager, L"asset/num.png", 10, 1);	// ���̉摜���g�p
		scoreNum.back()->SetPos((i * 60.0f) - 125.0f, 0.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}

	// �X�R�A�\��
	int tempScore = score;
	for (int i = static_cast<int>(scoreNum.size()) - 1; i >= 0; i--) {
		int digit = tempScore % 10;  // �E�[�̌����擾
		tempScore /= 10;            // �X�R�A��10�Ŋ����Ď��̌��֐i��

		// UV�����̒l�Ɋ�Â��Đݒ�
		scoreNum[i]->SetUV(digit, 0);
		//scorest.emplace_back(digit);
	}
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
	input.Update();

	if (state == 0) {
		// �X�R�A�����܂�܂œK���ɓ�����
		for (int i = 0; i < 5; i++) {
			scoreNum[i]->SetUV(rand() % 10, rand() % 10);
		}
		if (count == 300) {
			state = 1;
		}
		count++;
	}
	else if (state == 1) {

	}

	if (input.GetKeyTrigger(VK_1)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw() {
	result_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}