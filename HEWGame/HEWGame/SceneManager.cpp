//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "SceneManager.h"
#include "BaseScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "StageSelectScene.h"

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------

BaseScene* SceneManager::m_pNowScene = nullptr; // nullptr で初期化
BaseScene* SceneManager::m_pNextScene = nullptr;

//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void SceneManager::ChangeScene(SCENE scene,int num1, int num2, int num3) {
    switch (scene) {
    case SCENE::TITLE:
        m_pNextScene = new TitleScene(); // タイトルシーンを設定
        break;
    case SCENE::GAME:
        m_pNextScene = new GameScene(num1);  // ゲームシーンを設定
        break;
    case SCENE::RESULT:
        m_pNextScene = new ResultScene(num1, num2 , num3); // リザルトシーンを設定
        break;
    case SCENE::SELECT:
        m_pNextScene = new StageSelectScene(); // セレクトシーンを設定
        break;
    default:
        break;
    }
}

void SceneManager::SetScene()
{
    if (m_pNowScene != m_pNextScene) {
        delete m_pNowScene;
        m_pNowScene = m_pNextScene;
    }
}

void SceneManager::Update() {
    if (m_pNowScene) {
        m_pNowScene->Update(); // 現在のシーンの更新
    }
}

void SceneManager::Render() {
    if (m_pNowScene) {
        m_pNowScene->Draw(); // 現在のシーンの描画
    }
}


//******************************************************************************
//	End of file.
//******************************************************************************




