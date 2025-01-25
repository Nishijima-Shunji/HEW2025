#pragma once
class BaseScene;

class SceneManager {
private:
	static BaseScene* m_pNowScene;	//���݂̃V�[��
	static BaseScene* m_pNextScene;	//���̃V�[��

public:
	enum SCENE {
		TITLE,
		GAME,
		RESULT,
		SELECT
	};

	static void ChangeScene(SCENE scene,int num = 1);     //�V�[���������ɂ���ĕς���֐� 2�߂̈����Ő��l��n����(�Ȃɂ�����Ȃ��Ă������B���̏ꍇ��1������)
	void SetScene();	//�V�[���`�F���W�o�O�΍��p
	static void Update();                     //���݂̃V�[���̍X�V�֐�
	static void Render();                     //���݂̃V�[���̕`��֐�
};