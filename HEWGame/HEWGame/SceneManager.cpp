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

BaseScene* SceneManager::m_pScene = nullptr; // nullptr で初期化

//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void SceneManager::ChangeScene(SCENE scene,int stage) {
    if (m_pScene != nullptr) {
        delete m_pScene;
    }

    switch (scene) {
    case SCENE::TITLE:
        m_pScene = new TitleScene(); // タイトルシーンを設定
        break;
    case SCENE::GAME:
        m_pScene = new GameScene(stage);  // ゲームシーンを設定
        break;
    case SCENE::RESULT:
        m_pScene = new ResultScene(); // リザルトシーンを設定
        break;
    case SCENE::SELECT:
        m_pScene = new StageSelectScene(); // リザルトシーンを設定
        break;
    default:
        break;
    }
}

void SceneManager::Update() {
    if (m_pScene) {
        m_pScene->Update(); // 現在のシーンの更新
    }
}

void SceneManager::Render() {
    if (m_pScene) {
        m_pScene->Draw(); // 現在のシーンの描画
    }
}


//******************************************************************************
//	End of file.
//******************************************************************************




