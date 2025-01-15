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
std::vector<std::vector<int>> Light::Update(std::vector<std::vector<int>> MapDate)
{
	input.Update();

	//�}�b�v���̍X�V
	//=============================================================================================
	//�}�b�v�f�[�^���X�V����Ă�����

	if (Map != MapDate)
	{
		//�V�����}�b�v�����擾
		Map = MapDate;

		Width = 0;
		Height = 0;
		//�������擾
		for (int i = 0; i != 32; i++)
		{
			if (Map[0][i] != -1)
			{
				Width = i;
			}
		}
		//�������擾
		for (int j = 0; j != 16; j++)
		{
			if (Map[j][0] != 0)
			{
				Height = j;
			}
		}
	}

	//���W�擾
	//=============================================================================================
	Position();

	//���C�g�؂�ւ�
	//=============================================================================================
	Change();

	//�ړ�����
	//=============================================================================================
	Move();

	return Map;	//MapDate = Map
}

void Light::Change() {
	//���C�g�؂�ւ�
	//=============================================================================================
	if (input.GetKeyTrigger(VK_Q)) {	//�O�ɖ߂�
		if (Number != 0)
		{
			Number -= 1;
		}
	}
	if (input.GetKeyTrigger(VK_E)) {	//���ɐi��
		if (Number != 0)
		{
			Number += 1;
		}
	}
}

void Light::Position() {
	//���W�擾
	//=============================================================================================
	Lightpos_X.clear();
	Lightpos_Y.clear();

	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == 3)
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
		Count++;
	}
	//Y���W���X�g��N�Ԗڂ̐������擾
	Count = 0;
	for (auto i = Lightpos_Y.begin(); i != Lightpos_Y.end(); i++)
	{
		if (Count == Number)
		{
			Pos_Y = *i;
		}
		Count++;
	}
}

void Light::Move() {
	//�ړ�����
	//=============================================================================================

	//�Â����W�����擾
	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	//��Ɉړ������m
	if (input.GetKeyTrigger(VK_W)) {
		//�E���[���ɑ���
		if (Pos_Y == Width)
		{
			//���C�g�������E
			Direction = 2;

			//��[�ɂ���
			if (Pos_X == 1)
			{
				//�㕔���[���Ɉړ�
				Pos_X -= 1;
				//���ɂP�}�X�����
				Pos_Y -= 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_X -= 1;
			}
		}
		//�����[���ɑ���
		else if (Pos_Y == 0)
		{
			//���C�g��������
			Direction = 3;

			//��[�ɂ���
			if (Pos_X == 1)
			{
				//�㕔���[���Ɉړ�
				Pos_X -= 1;
				//�E�ɂP�}�X�����
				Pos_Y += 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_X -= 1;
			}
		}

		LightOn = false;
	}

	//���Ɉړ������m
	if (input.GetKeyTrigger(VK_S)) {
		//�E���[���ɑ���
		if (Pos_Y == Width)
		{
			//���C�g�������E
			Direction = 2;

			//���[�ɂ���
			if (Pos_X == Height - 1)
			{
				//�������[���Ɉړ�
				Pos_X += 1;
				//���ɂP�}�X�����
				Pos_Y -= 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_X += 1;
			}
		}
		//�����[���ɑ���
		else if (Pos_Y == 0)
		{
			//���C�g��������
			Direction = 3;

			//���[�ɂ���
			if (Pos_X == Height - 1)
			{
				//�������[���Ɉړ�
				Pos_X += 1;
				//�E�ɂP�}�X�����
				Pos_Y += 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_X += 1;
			}
		}

		LightOn = false;
	}

	//�E�Ɉړ������m
	if (input.GetKeyTrigger(VK_D)) {
		//�㕔���[���ɑ���
		if (Pos_X == 0)
		{
			//���C�g��������
			Direction = 0;

			//�E�[�ɂ���
			if (Pos_Y == Width - 1)
			{
				//�E���[���Ɉړ�
				Pos_Y += 1;
				//�P�}�X������
				Pos_X += 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_Y += 1;
			}
		}
		//�������[���ɑ���
		else if (Pos_X == Height)
		{
			//���C�g��������
			Direction = 1;

			//�E�[�ɂ���
			if (Pos_Y == Width - 1)
			{
				//�E���[���Ɉړ�
				Pos_Y += 1;
				//�P�}�X�オ��
				Pos_X -= 1;
				//90�x��]
				SetAngle(270);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_Y += 1;
			}
		}

		LightOn = false;
	}

	//���Ɉړ������m
	if (input.GetKeyTrigger(VK_A)) {
		//�㕔���[���ɑ���
		if (Pos_X == 0)
		{
			//���C�g��������
			Direction = 0;

			//���[�ɂ���Ȃ�
			if (Pos_Y == 1)
			{
				//�����[���Ɉړ�
				Pos_Y -= 1;
				//�P�}�X������
				Pos_X += 1;
				//90�x��]
				SetAngle(90);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_Y -= 1;
			}
		}
		//�������[���ɑ���
		else if (Pos_X == Height)
		{
			//���C�g��������
			Direction = 1;

			//���[�ɂ���Ȃ�
			if (Pos_Y == 1)
			{
				//�����[���Ɉړ�
				Pos_Y -= 1;
				//�P�}�X�オ��
				Pos_X -= 1;
				//90�x��]
				SetAngle(90);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_Y -= 1;
			}
		}

		LightOn = false;
	}


	//���C�g�̓_�������m
	if (input.GetKeyTrigger(VK_SPACE))
	{
		if (LightOn == true)
		{
			LightOn = false;
		}
		else if (LightOn == false)
		{
			LightOn = true;
		}
		Flash();
	}


	//���C�g�̍��W���X�V����Ă���Ȃ�
	if (Old_Pos_X != Pos_X || Old_Pos_Y != Pos_Y)
	{
		Flash();
		MapUpdate();
	}

}

void Light::Flash() {
	//��������
	//=============================================================================================
	if (LightOn == true)
	{
		if (Pos_X == 0)
		{
			Direction = 0;
		}
		else if (Pos_X == Height)
		{
			Direction = 1;
		}
		else if (Pos_Y == Width)
		{
			Direction = 2;
		}
		else if (Pos_Y == 0)
		{
			Direction = 3;
		}

		//��
		if (Direction == 0)
		{
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X�����i0�j�Ȃ�
				if (Map[Pos_X + i][Pos_Y] == 0)
				{
					//������ԁi�T�j�ɕς���
					Map[Pos_X + i][Pos_Y] = 5;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Pos_X + i][Pos_Y] == 1)
				{
					//��~
					Stop = true;
				}
				//���̃}�X��������ԁi�T�j�Ȃ�
				else if (Map[Pos_X + i][Pos_Y] == 5)
				{
					//����
				}
			}
		}
		//��
		else if (Direction == 1)
		{
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X�����i0�j�Ȃ�
				if (Map[Pos_X - i][Pos_Y] == 0)
				{
					//������ԁi�T�j�ɕς���
					Map[Pos_X - i][Pos_Y] = 5;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Pos_X - i][Pos_Y] == 1)
				{
					//��~
					Stop = true;
				}
				//���̃}�X��������ԁi�T�j�Ȃ�
				else if (Map[Pos_X - i][Pos_Y] == 5)
				{
					//����
				}
			}
		}
		//�E
		else if (Direction == 2)
		{
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X�����i0�j�Ȃ�
				if (Map[Pos_X][Pos_Y - i] == 0)
				{
					//������ԁi�T�j�ɕς���
					Map[Pos_X][Pos_Y - i] = 5;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Pos_X][Pos_Y - i] == 1)
				{
					//��~
					Stop = true;
				}
				//���̃}�X��������ԁi�T�j�Ȃ�
				else if (Map[Pos_X][Pos_Y - i] == 5)
				{
					//����
				}
			}
		}
		//��
		else if (Direction == 3)
		{
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X�����i0�j�Ȃ�
				if (Map[Pos_X][Pos_Y + i] == 0)
				{
					//������ԁi�T�j�ɕς���
					Map[Pos_X][Pos_Y + i] = 5;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Pos_X][Pos_Y + i] == 1)
				{
					//��~
					Stop = true;
				}
				//���̃}�X��������ԁi�T�j�Ȃ�
				else if (Map[Pos_X][Pos_Y + i] == 5)
				{
					//����
				}
			}
		}
	}
	else if (LightOn == false)
	{
		Stop = false;

		//��
		if (Direction == 0)
		{
			//�Փ˔���܂łɖ��i0�j�ς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X��������ԁi�T�j�Ȃ�
				if (Map[Old_Pos_X + i][Old_Pos_Y] == 5)
				{
					//���i0�j�ɕς���
					Map[Old_Pos_X + i][Old_Pos_Y] = 0;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Old_Pos_X + i][Old_Pos_Y] == 1)
				{
					//��~
					Stop = true;
				}
			}
		}
		//��
		else if (Direction == 1)
		{
			//�Փ˔���܂Ŗ��i0�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X��������ԁi�T�j�Ȃ�
				if (Map[Old_Pos_X - i][Old_Pos_Y] == 5)
				{
					//���i0�j�ɕς���
					Map[Old_Pos_X - i][Old_Pos_Y] = 0;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Old_Pos_X - i][Old_Pos_Y] == 1)
				{
					//��~
					Stop = true;
				}
			}
		}
		//�E
		else if (Direction == 2)
		{
			//�Փ˔���܂Ŗ��i0�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X��������ԁi�T�j�Ȃ�
				if (Map[Old_Pos_X][Old_Pos_Y - i] == 5)
				{
					//���i0�j�ɕς���
					Map[Old_Pos_X][Old_Pos_Y - i] = 0;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Old_Pos_X][Old_Pos_Y - i] == 1)
				{
					//��~
					Stop = true;
				}
			}
		}
		//��
		else if (Direction == 3)
		{
			//�Փ˔���܂Ŗ��i0�j�ɕς���
			for (int i = 1; Stop != true; i++)
			{
				//���̃}�X��������ԁi�T�j�Ȃ�
				if (Map[Old_Pos_X][Old_Pos_Y + i] == 5)
				{
					//���i0�j�ɕς���
					Map[Old_Pos_X][Old_Pos_Y + i] = 0;
				}
				//���̃}�X���ǁi1�j�Ȃ�
				else if (Map[Old_Pos_X][Old_Pos_Y + i] == 1)
				{
					//��~
					Stop = true;
				}
			}
		}
		Stop = false;
	}
}

std::vector<std::vector<int>> Light::MapUpdate()
{
	//�}�b�v�f�[�^�X�V
	//=============================================================================================
	Map[Old_Pos_X][Old_Pos_Y] = 1;	//�ǂɖ߂�
	Map[Pos_X][Pos_Y] = 3;	//���C�g���ړ�
	//DebugMap();
	return Map;
}

void Light::DebugMap()
{
	std::cout << "�}�b�v�X�V" << std::endl;
	//�f�o�b�O	�}�b�v���l�\��
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			std::cout << Map[i][j] << ",";
		}
		std::cout << std::endl;
	}
	//======================
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

��
���C�g
�v���C���[
�G�l�~�[

���C�g���x
1�F����
2�F�T�}�X
3�F�R�}�X
*/