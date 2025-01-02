#pragma once
class BaseScene;

class SceneManager {
private:
	static BaseScene* m_pScene;               //現在のシーン

public:
	enum SCENE {
		TITLE,
		GAME,
		RESULT,
		SELECT
	};
	static void ChangeScene(SCENE scene,int stage = 1);     //シーンを引数によって変える関数
	static void Update();                     //現在のシーンの更新関数
	static void Render();                     //現在のシーンの描画関数
};