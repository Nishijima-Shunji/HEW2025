#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene(int score) : Score(score) {
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
		scoreNum.back()->SetPos((i * 60.0f) + 120.0f, 0.0f, 0.0f);
		scoreNum.back()->SetSize(60.0f, 60.0f, 0.0f);
		scoreNum.back()->SetUV(0, 0);
	}
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
    input.Update();

    if (state == 0) {
        // �����������ŉ�
        for (int i = 0; i < 5; i++) {
            scoreNum[i]->SetUV(rand() % 10,0);
        }
        if (count == 100) {
            state = 1;          // �X�R�A�m��ֈڍs
            revealIndex = 0;    // ���̕\���J�n�ʒu
            count = 0;          // �J�E���g���Z�b�g
        }
    }
    else if (state == 1) {
        // �����E���珇��1���Œ�
        if (count % 8 == 0 && revealIndex < static_cast<int>(scoreNum.size())) {
            int digit = tempScore % 10;  // �E�[�̌����擾
            tempScore /= 10;             // ���̌���
            scoreNum[scoreNum.size() - 1 - revealIndex]->SetUV(digit, 0);
            revealIndex++;
        }

        // �m�肵�����͌Œ肵�A���m��̌��͈������������_���\��
        for (int i = 0; i < static_cast<int>(scoreNum.size()) - revealIndex; i++) {
            scoreNum[i]->SetUV(rand() % 10,0);
        }

        // �S���m���A���̏�Ԃ�
        if (revealIndex >= static_cast<int>(scoreNum.size())) {
            state = 2;
        }
    }

    if (input.GetKeyTrigger(VK_1)) {
        SceneManager::ChangeScene(SceneManager::TITLE);
    }
    count++;
}

void ResultScene::Draw() {
	result_bg->Draw();
	for (auto& obj : scoreNum) {
		obj->Draw();
	}
}