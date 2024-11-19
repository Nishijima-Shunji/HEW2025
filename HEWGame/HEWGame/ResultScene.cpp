#include "ResultScene.h"
#include "Game.h"

ResultScene::ResultScene() {
	TextureManager* textureManager = new TextureManager(g_pDevice);

	result_bg = new Object;
	result_bg->Init(textureManager, L"asset/Result_test.png", 8, 4);
	result_bg->SetPos(0.0f, 0.0f, 0.0f);	//�ʒu��ݒ�
	result_bg->SetSize(300.0f, 300.0f, 0.0f);	//�傫����ݒ�
	result_bg->SetAngle(0.0f);	//�p�x��ݒ�
	result_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//�F��ݒ�
}

ResultScene::~ResultScene() {
	delete result_bg;
}

void ResultScene::Update() {
	input.Update();
	if (input.GetKeyTrigger(VK_1)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ResultScene::Draw() {
	result_bg->Draw();
}