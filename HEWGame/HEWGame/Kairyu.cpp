//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Kairyu.h"
#include "GameScene.h"

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------


//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================

void Kairyu::Init()
{

}

//void  Kairyu::Update(GameScene* game)
std::vector<std::vector<int>> Kairyu::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	Map = MapData;
	// GameScene ���� characterObj ���擾
	auto& characterObj = game.GetCharacterObjects(); // �Q�Ƃ��g��

	for (const auto& obj : characterObj) {
		// Player �I�u�W�F�N�g���ǂ������m�F
		Player* player = dynamic_cast<Player*>(obj.get());
		if (player) {
			float deltaX = 0.0f;
			if (this->CheckCollision(*player)) {
				// �E
				if (direction == 0) {
					deltaX = 1.0f;
				}
				// ��
				else if (direction == 1) {
					deltaX = -1.0f;
				}

				// �v���C���[�̈ʒu���X�V
				player->SetPos(player->GetPos().x + deltaX, player->GetPos().y, 0.0f);

				break; // ���[�v���I��
			}
		}
	}
		// �ҋ@�A�j���[�V����
	SetUV(animcount % 4, (animcount / 4) % 2);
	if (framecount % 5 == 0) {
		animcount++;
	}

	framecount++;
	return Map;
}

void Kairyu::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
