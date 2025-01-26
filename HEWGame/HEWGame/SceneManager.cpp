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

BaseScene* SceneManager::m_pNowScene = nullptr; // nullptr �ŏ�����
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
        m_pNextScene = new TitleScene(); // �^�C�g���V�[����ݒ�
        break;
    case SCENE::GAME:
        m_pNextScene = new GameScene(num1);  // �Q�[���V�[����ݒ�
        break;
    case SCENE::RESULT:
        m_pNextScene = new ResultScene(num1, num2 , num3); // ���U���g�V�[����ݒ�
        break;
    case SCENE::SELECT:
        m_pNextScene = new StageSelectScene(); // �Z���N�g�V�[����ݒ�
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
        m_pNowScene->Update(); // ���݂̃V�[���̍X�V
    }
}

void SceneManager::Render() {
    if (m_pNowScene) {
        m_pNowScene->Draw(); // ���݂̃V�[���̕`��
    }
}


//******************************************************************************
//	End of file.
//******************************************************************************




