#include "TitleScene.h"
#include "Game.h"
#include <cstdlib>  // rand()��srand()�̂���
#include <ctime>    // time()�̂���

TitleScene::TitleScene() {
    TextureManager* textureManager = new TextureManager(g_pDevice);

    // �^�C�g���w�i====================
    title_bg = new Object;  // �I�u�W�F�N�g����
    title_bg->Init(textureManager, L"asset/Bg/sea.png", 8, 4);
    title_bg->SetPos(0.0f, 0.0f, 0.0f);  // �ʒu��ݒ�
    title_bg->SetSize(1000.0f, 500.0f, 0.0f);  // �傫����ݒ�
    title_bg->SetAngle(0.0f);  // �p�x��ݒ�
    title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // �F��ݒ�

    // �^�C�g����=======================
    title_name = new Object;
    title_name->Init(textureManager, L"asset/Title_test.png", 8, 4);
    title_name->SetPos(0.0f, 0.0f, 1.0f);  // �ʒu��ݒ�
    title_name->SetSize(300.0f, 300.0f, 0.0f);  // �傫����ݒ�
    title_name->SetAngle(0.0f);  // �p�x��ݒ�
    title_bg->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // �F��ݒ�

    // �^�C�g���I�u�W�F�N�g=============
    InitTitleObjects(10);  // �����_���Ȉʒu��10�̃I�u�W�F�N�g��������
}

TitleScene::~TitleScene() {
    delete title_bg;
    delete title_name;
    for (auto obj : title_Ob) {
        delete obj;
    }
}

void TitleScene::InitTitleObjects(int count) {
    TextureManager* textureManager = new TextureManager(g_pDevice);
    srand(static_cast<unsigned>(time(0)));  // �����_���������̂��߂̃V�[�h

    for (int i = 0; i < count; ++i) {
        Object* obj = new Object;
        obj->Init(textureManager, L"asset/Bg/konbu.png", 8, 4);
        float x = static_cast<float>((rand() % 1000)-500);  // �����_����x�ʒu
        float y = static_cast<float>((rand() % 500)-400);   // �����_����y�ʒu
        // y�̒l���������قǑ傫������
        float sizeFactor_Bg = 1.0f + (25.0f - y) / 25.0f;  // y���������ق�sizeFactor���傫���Ȃ�
        float width_konbu = 10.0f * sizeFactor_Bg;//���z�̕�
        float height_konbu = 10.0f * sizeFactor_Bg;//����
        obj->SetPos(x, y, 1.0f);  // �ʒu��ݒ�
        obj->SetSize(width_konbu, height_konbu, 0.0f);  // �傫����ݒ�
        obj->SetAngle(0.0f);  // �p�x��ݒ�
        obj->SetColor(1.0f, 1.0f, 1.0f, 1.0f);  // �F��ݒ�
        title_Ob.push_back(obj);
    }
}

// �V�[���̃A�b�v�f�[�g
void TitleScene::Update() {
    input.Update();  // �L�[���͂̔���
    if (input.GetKeyTrigger(VK_2)) {
        SceneManager::ChangeScene(SceneManager::SELECT);  // �V�[����GAME�ֈڍs
    }
}

// �e�V�[���̕`��
void TitleScene::Draw() {
    title_bg->Draw();
    title_name->Draw();
    for (auto obj : title_Ob) {
        obj->Draw();
    }
}