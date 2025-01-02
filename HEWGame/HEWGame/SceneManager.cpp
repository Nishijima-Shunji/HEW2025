//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
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
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------

BaseScene* SceneManager::m_pScene = nullptr; // nullptr �ŏ�����

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
        m_pScene = new TitleScene(); // �^�C�g���V�[����ݒ�
        break;
    case SCENE::GAME:
        m_pScene = new GameScene(stage);  // �Q�[���V�[����ݒ�
        break;
    case SCENE::RESULT:
        m_pScene = new ResultScene(); // ���U���g�V�[����ݒ�
        break;
    case SCENE::SELECT:
        m_pScene = new StageSelectScene(); // ���U���g�V�[����ݒ�
        break;
    default:
        break;
    }
}

void SceneManager::Update() {
    if (m_pScene) {
        m_pScene->Update(); // ���݂̃V�[���̍X�V
    }
}

void SceneManager::Render() {
    if (m_pScene) {
        m_pScene->Draw(); // ���݂̃V�[���̕`��
    }
}


//******************************************************************************
//	End of file.
//******************************************************************************




