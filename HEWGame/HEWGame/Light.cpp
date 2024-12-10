//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Light.h"
#include "Input.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
Input input;



//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================

Light::Light() {
	Mode = 0;

	Old_Pos_X = 0;
	Old_Pos_Y = 0;
	Pos_X = 0;
	Pos_Y = 0;
	Count;
	Number = 1;
}

void Light::Update(int WidthMAX, int HeightMAX, std::vector<std::vector<int>> MapData)
{
	//�����@�F�@�����A�����A�}�b�v�f�[�^


	switch (Mode)
	{
	case 0:
		//���C�g�؂�ւ�
		//=============================================================================================
		if (input.GetKeyTrigger(VK_Q)) {	//�O�ɖ߂�
			if (Number != 0)
			{
				Number -= 1;
				Mode++;
			}
		}
		if (input.GetKeyTrigger(VK_E)) {	//���ɐi��
			if (Number != 0)
			{
				Number += 1;
				Mode++;
			}
		}
		break;
	case 1:
		//���W�擾
		//=============================================================================================
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 32; j++) {
				if (MapData[i][j] == 3)
				{
					Lightpos_X.push_back(i);
					Lightpos_Y.push_back(j);
				}
			}
		}
		//X���W���X�g��N�Ԗڂ̐������擾
		Count = 0;
		for (auto i = Lightpos_X.begin(); i != Lightpos_X.end(); i++)
		{
			if (Count == Number)
			{
				Pos_X = *i;
			}
		}
		//Y���W���X�g��N�Ԗڂ̐������擾
		Count = 0;
		for (auto i = Lightpos_Y.begin(); i != Lightpos_Y.end(); i++)
		{
			if (Count == Number)
			{
				Pos_Y = *i;
			}
		}
		Mode = 0;
		break;
	}

	//�ړ�����
	//===========================================================================================

	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	if (input.GetKeyTrigger(VK_A)) {
		//�c�Œ�
		if (Pos_Y <= 1) {
			//�����[���Ɉړ�
			Pos_Y -= 1;
			Pos_X += 1;
		}
		else {
			Pos_Y -= 1;
		}
	}

	/*
	//���Ɉړ�
	if (input.GetKeyTrigger(VK_A)) {
		//�c�Œ�
		if (Pos_Y <= 1) {
			//�����[���Ɉړ�
			Pos_Y -= 1;
			Pos_X += 1;
		}
		else {
			Pos_Y -= 1;
		}
	}
	//�E�Ɉړ�
	if (input.GetKeyTrigger(VK_D)) {
		//�c�Œ�
		if (Pos_Y >= WidthMAX - 1) {
			//�E���[���Ɉړ�
			Pos_Y += 1;
			Pos_X += 1;
		}
		else {
			Pos_Y += 1;
		}
	}

	//��Ɉړ�
	if (input.GetKeyTrigger(VK_W)) {
		//�c�Œ�
		if (Pos_X >= 1) {
			Pos_X -= 1;
			Pos_Y += 1;
		}
		else {
			Pos_X -= 1;
		}

	}

	//���Ɉړ�
	if (input.GetKeyTrigger(VK_S)) {
		//�c�Œ�
		if (Pos_Y >= HeightMAX - 1) {
			Pos_X += 1;
			Pos_Y += 1;
		}
		else {
			Pos_X += 1;
		}
	}*/


}

//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================

std::vector<std::vector<int>> Light::Map(std::vector<std::vector<int>> MapData)
{
	//�}�b�v�f�[�^�X�V
	//===========================================================================================
	MapData[Old_Pos_X][Old_Pos_Y] = 1;	//�ǂɖ߂�
	MapData[Pos_X][Pos_Y] = 3;	//���C�g���ړ�

	return MapData;
}

//******************************************************************************
//	End of file.
//******************************************************************************

/*
18�~32

�����Ȃ�
�Èŏ��	100
�������	200
�_�����	300

���C�g���x
1�F����
2�F�T�}�X
3�F�R�}�X
*/
/*
switch (Mode)
{
case 0:
	//���C�g�؂�ւ�
	//=============================================================================================
	if (input.GetKeyTrigger(VK_Q)) {	//�O�ɖ߂�
		if (Number != 0)
		{
			Number -= 1;
			Mode++;
		}
	}
	if (input.GetKeyTrigger(VK_E)) {	//���ɐi��
		if (Number != 0)
		{
			Number += 1;
			Mode++;
		}
	}
	break;
case 1:
	//���W�擾
	//=============================================================================================
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (MapData[i][j] == 3)
			{
				Lightpos_X.push_back(i);
				Lightpos_Y.push_back(j);
			}
		}
	}
	//X���W���X�g��N�Ԗڂ̐������擾
	Count = 0;
	for (auto i = Lightpos_X.begin(); i != Lightpos_X.end(); i++)
	{
		if (Count == Number)
		{
			Pos_X = *i;
		}
	}
	//Y���W���X�g��N�Ԗڂ̐������擾
	Count = 0;
	for (auto i = Lightpos_Y.begin(); i != Lightpos_Y.end(); i++)
	{
		if (Count == Number)
		{
			Pos_Y = *i;
		}
	}
	Mode = 0;
	break;
}
*/