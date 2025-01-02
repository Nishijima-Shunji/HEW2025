#pragma once
class BaseScene;

class SceneManager {
private:
	static BaseScene* m_pScene;               //���݂̃V�[��

public:
	enum SCENE {
		TITLE,
		GAME,
		RESULT,
		SELECT
	};
	static void ChangeScene(SCENE scene,int stage = 1);     //�V�[���������ɂ���ĕς���֐�
	static void Update();                     //���݂̃V�[���̍X�V�֐�
	static void Render();                     //���݂̃V�[���̕`��֐�
};