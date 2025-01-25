#pragma once
class BaseScene;

class SceneManager {
private:
	static BaseScene* m_pNowScene;	//現在のシーン
	static BaseScene* m_pNextScene;	//次のシーン

public:
	enum SCENE {
		TITLE,
		GAME,
		RESULT,
		SELECT
	};

	static void ChangeScene(SCENE scene,int num = 1);     //シーンを引数によって変える関数 2つめの引数で数値を渡せる(なにも入れなくてもいい。その場合は1が入る)
	void SetScene();	//シーンチェンジバグ対策用
	static void Update();                     //現在のシーンの更新関数
	static void Render();                     //現在のシーンの描画関数
};