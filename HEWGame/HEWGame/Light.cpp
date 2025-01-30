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
std::vector<std::vector<int>> Light::Update(std::vector<std::vector<int>> MapData)
{
	input.Update();

	//�}�b�v���̍X�V
	//=============================================================================================
	//�}�b�v�f�[�^���X�V����Ă�����

	//�V�����}�b�v�����擾
	Map = MapData;
	
	if (SetUp == false)
	{
		Width = 0;
		Height = 0;
		//�������擾
		for (int i = 0; i != 32; i++)
		{
			//if (Map[0][i] != NOTHING)
			if (Map[0][i] != -9)
			{
				Width = i;
			}
		}
		//�������擾
		for (int j = 0; j != 16; j++)
		{
			//if (Map[j][0] != NOTHING)
			if (Map[j][0] != -9)
			{
				Height = j;
			}
		}

		//���W�擾
		//===============================================================================================
		Position();

		//�M�~�b�N�擾
		//===============================================================================================
		SetGimmick();

		SetUp = true;
	}

	

	//���C�g�؂�ւ�
	//=============================================================================================
	Change();

	//�ړ�����
	//=============================================================================================
	Move();


	//��������
	//=============================================================================================
	Flash();

	//�}�b�v�f�[�^�X�V
	//=============================================================================================
	MapUpdate();

	return Map;	//MapDate = Map
}
void Light::SetGimmick()
{
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == WALL)
			{   //�ǂ�o�^

				Gimmick[i][j] = WALL;
			}
			else if (Map[i][j] == MIRROR_U)
			{   //����i�E�オ��j��o�^

				Gimmick[i][j] = MIRROR_U;
				Map[i][j] = NOTHING;
			}
			else if (Map[i][j] == MIRROR_D)
			{   //����i�E������j��o�^

				Gimmick[i][j] = MIRROR_D;
				Map[i][j] = NOTHING;
			}
			else if (Map[i][j] == MOB_2)
			{   //�`���E�`���A���R�E��o�^

				Gimmick[i][j] = MOB_2;
				Map[i][j] = NOTHING;
			}
			else
			{
				//	Gimmick[i][j] = SPACE;
			}
		}
	}
}

void Light::Change() {
	//���C�g�؂�ւ�
	//=============================================================================================
	if (input.GetKeyTrigger(VK_Q) || input.GetButtonTrigger(XINPUT_LEFT_SHOULDER)) {	//�O�ɖ߂�
		if (Number != 1)
		{
			int num = 10000 + (Pos_X * 100 + Pos_Y);
			Lightpos[Number] = num;
			Number--;
			Pos_X = Lightpos[Number] / 100 - 100;
			Pos_Y = Lightpos[Number] % 100;
		}
	}
	if (input.GetKeyTrigger(VK_E) || input.GetButtonTrigger(XINPUT_RIGHT_SHOULDER)) {	//���ɐi��
		if (Number != LightMAX)//���C�g�̓o�^���
		{
			int num = 10000 + (Pos_X * 100 + Pos_Y);
			Lightpos[Number] = num;
			Number++;
			Pos_X = Lightpos[Number] / 100 - 100;
			Pos_Y = Lightpos[Number] % 100;
		}
	}
}

void Light::Position() {
	//���W�擾
	//=============================================================================================
	Lightpos.push_back(99999);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == 12 || Map[i][j] == 13 || Map[i][j] == 14 || Map[i][j] == 19)
			{
				int num = 10000 + (i * 100 + j);
				Lightpos.push_back(num);
				LightMAX++;
			}
		}
	}

	Pos_X = Lightpos[Number] / 100 - 100;
	Pos_Y = Lightpos[Number] % 100;
}

void Light::Move() 
{
	//�Â����W�����擾
	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	//��Ɉړ������m
	if (input.GetKeyTrigger(VK_W) || input.GetButtonTrigger(XINPUT_UP)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_S) || input.GetButtonTrigger(XINPUT_DOWN)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_D) || input.GetButtonTrigger(XINPUT_RIGHT)) {
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
				angle -= 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_A) || input.GetButtonTrigger(XINPUT_LEFT)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle += 90;
				SetAngle(angle);
			}
			//����ȊO�Ȃ�
			else
			{
				Pos_Y -= 1;
			}
		}

		LightOn = false;
	}

}

void Light::Spin()
{

}

void Light::Flash() 
{
	//���C�g�̓_�������m
	if (input.GetKeyTrigger(VK_SPACE) || input.GetButtonTrigger(XINPUT_A))
	{
		if (LightOn == true)
		{
			LightOn = false;
		}
		else if (LightOn == false)
		{
			LightOn = true;
		}

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
	}

	//DebugMap();
	if (LightOn == true)
	{
		Stop = false;

		//��
		if (Direction == 0)
		{
			int i = 0;
			//�Փ˔��肪�ł�܂�
			for (; Stop != true; i++)
			{
				Pos_X += 1;//���W��ύX

				//��/���
				if (Map[Pos_X][Pos_Y] == NOTHING || Map[Pos_X][Pos_Y] == SPACE) { Map[Pos_X][Pos_Y] = Luminous; }//����
				//�S�[��
				else if (Map[Pos_X][Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Pos_X][Pos_Y] == P_DIVER) { Map[Pos_X][Pos_Y] = Luminous; }
				//�T��
				else if (Map[Pos_X][Pos_Y] == E_SHARK) { Map[Pos_X][Pos_Y] = Luminous; }
				//�����}�X
				else if (Map[Pos_X][Pos_Y] == Luminous)
				{
					//����
				}

				//����i�E�オ��j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_U)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//�@��
					//���^
					Direction = 2;
					Flash();
				}
				//����i��������j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_D)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//��
					//�_��
					Direction = 3;
					Flash();
				}
				//�I�j�L����
				else if (Gimmick[Pos_X][Pos_Y] == MOB_1)
				{
					//
				}
				//�A���R�E
				else if (Gimmick[Pos_X][Pos_Y] == MOB_2)
				{
					//
				}
				//��/�}�b�v�[/���C�g
				else { Stop = true; }//��~
			}
			Pos_X = Pos_X - i;
		}
		//��
		else if (Direction == 1)
		{
			int i = 0;
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (; Stop != true; i++)
			{
				Pos_X -= 1;

				//��/���
				if (Map[Pos_X][Pos_Y] == NOTHING || Map[Pos_X][Pos_Y] == SPACE) { Map[Pos_X][Pos_Y] = Luminous; }//������ԁi20�j�ɕς���
				//�S�[��
				else if (Map[Pos_X][Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Pos_X][Pos_Y] == P_DIVER) { Map[Pos_X][Pos_Y] = Luminous; }
				//�T��
				else if (Map[Pos_X][Pos_Y] == E_SHARK) { Map[Pos_X][Pos_Y] = Luminous; }
				//�����}�X
				else if (Map[Pos_X][Pos_Y] == Luminous)
				{
					//����
				}

				//����i�E�オ��
				else if (Gimmick[Pos_X - i][Pos_Y] == MIRROR_U)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//�^��
					//��
					Direction = 3;
					Flash();
				}
				//����i��������
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_D)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//���_
					//�@��
					Direction = 2;
					Flash();
				}
				//�I�j�L����
				else if (Gimmick[Pos_X][Pos_Y] == MOB_1)
				{
					//
				}
				//�A���R�E
				else if (Gimmick[Pos_X][Pos_Y] == MOB_2)
				{
					//
				}
				//��/�S�[��/�}�b�v�[/���C�g
				else { Stop = true; }//��~
			}
			Pos_X = Pos_X + i;
		}
		//�E
		else if (Direction == 2)
		{
			int i = 0;
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (; Stop != true; i++)
			{
				Pos_Y -= 1;
				//��/���
				if (Map[Pos_X][Pos_Y] == NOTHING || Map[Pos_X][Pos_Y] == SPACE) { Map[Pos_X][Pos_Y] = Luminous; }//������ԁi20�j�ɕς���
				//�S�[��
				else if (Map[Pos_X][Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Pos_X][Pos_Y] == P_DIVER) { Map[Pos_X][Pos_Y] = Luminous; }
				//�T��
				else if (Map[Pos_X][Pos_Y] == E_SHARK) { Map[Pos_X][Pos_Y] = Luminous; }
				//�����}�X
				else if (Map[Pos_X][Pos_Y] == Luminous)
				{
					//����
				}

				//����i�E�オ��j�i6�j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_U)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//�^��
					//��
					Direction = 0;
					Flash();
				}
				//����i��������j�i7�j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_D)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//��
					//�_��
					Direction = 1;
					Flash();
				}
				//�I�j�L����
				else if (Gimmick[Pos_X][Pos_Y] == MOB_1)
				{
					//
				}
				//�A���R�E
				else if (Gimmick[Pos_X][Pos_Y] == MOB_2)
				{
					//
				}
				//��/�S�[��/�}�b�v�[/���C�g
				else { Stop = true; }//��~
			}
			Pos_Y = Pos_Y + i;
		}
		//��
		else if (Direction == 3)
		{
			int i = 0;
			//�Փ˔���܂Ŕ�����ԁi�T�j�ɕς���
			for (; Stop != true; i++)
			{
				Pos_Y += 1;
				//��/���
				if (Map[Pos_X][Pos_Y] == NOTHING || Map[Pos_X][Pos_Y] == SPACE) { Map[Pos_X][Pos_Y] = Luminous; }//������ԁi20�j�ɕς���
				//�S�[��
				else if (Map[Pos_X][Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Pos_X][Pos_Y] == P_DIVER) { Map[Pos_X][Pos_Y] = Luminous; }
				//�T��
				else if (Map[Pos_X][Pos_Y] == E_SHARK) { Map[Pos_X][Pos_Y] = Luminous; }
				//�����}�X
				else if (Map[Pos_X][Pos_Y] == Luminous)
				{
					//����
				}

				//����i�E�オ��j�i6�j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_U)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;
					//���˂���
					//�@��
					//���^
					Direction = 1;
					Flash();
				}
				//����i��������j�i7�j
				else if (Gimmick[Pos_X][Pos_Y] == MIRROR_D)
				{
					//������ԁi20�j�ɕς���
					Map[Pos_X][Pos_Y] = Luminous;

					//���˂���
					//���_
					//�@��
					Direction = 0;
					Flash();
				}
				//�I�j�L����
				else if (Gimmick[Pos_X][Pos_Y] == MOB_1)
				{
					//
				}
				//�A���R�E
				else if (Gimmick[Pos_X][Pos_Y] == MOB_2)
				{
					//
				}
				//��/�S�[��/�}�b�v�[/���C�g
				else { Stop = true; }//��~
			}

			Pos_Y = Pos_Y - i;
		}
	}
	else if (LightOn == false)
	{
		Stop = false;

		//��
		if (Direction == 0)
		{
			int i = 0;
			//�Փ˔��肪�ł�܂�
			for (; Stop != true; i++)
			{
				Old_Pos_X += 1;//���W��ύX

				//��
				if (Map[Old_Pos_X][Old_Pos_Y] == NOTHING)
				{
//					std::cout << "�G���[:Light" << std::endl;
					//��~
					Stop = true;
				}
				//���
				else if (Map[Old_Pos_X][Old_Pos_Y] == SPACE) {}
				//�S�[��
				else if (Map[Old_Pos_X][Old_Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Old_Pos_X][Old_Pos_Y] == P_DIVER) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�T��
				//else if (Map[Old_Pos_X][Old_Pos_Y] == E_SHARK) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�����}�X
				else if (Map[Old_Pos_X][Old_Pos_Y] == Luminous)
				{
					//��Ԃɕς���
					Map[Old_Pos_X][Old_Pos_Y] = SPACE;
				}
				//����i�E�オ��j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_U)
				{
					//���˂���
					//�@��
					//���^
					Direction = 2;
					Flash();
				}
				//����i��������j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_D)
				{
					//���˂���
					//��
					//�_��
					Direction = 3;
					Flash();
				}
				else
				{
					//��~
					Stop = true;
				}

			}
			Old_Pos_X = Old_Pos_X - i;
		}
		//��
		else if (Direction == 1)
		{
			int i = 0;
			//�Փ˔��肪�ł�܂�
			for (; Stop != true; i++)
			{
				Old_Pos_X -= 1;//���W��ύX

				//��
				if (Map[Old_Pos_X][Old_Pos_Y] == NOTHING)
				{
//					std::cout << "�G���[:Light" << std::endl;
					//��~
					Stop = true;
				}
				//���
				else if (Map[Old_Pos_X][Old_Pos_Y] == SPACE) {}
				//�S�[��
				else if (Map[Old_Pos_X][Old_Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Old_Pos_X][Old_Pos_Y] == P_DIVER) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�T��
				//else if (Map[Old_Pos_X][Old_Pos_Y] == E_SHARK) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�����}�X
				else if (Map[Old_Pos_X][Old_Pos_Y] == Luminous)
				{
					//��Ԃɕς���
					Map[Old_Pos_X][Old_Pos_Y] = SPACE;
				}
				//����i�E�オ��j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_U)
				{
					//���˂���
					//�@��
					//���^
					Direction = 3;
					Flash();
				}
				//����i��������j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_D)
				{
					//���˂���
					//��
					//�_��
					Direction = 2;
					Flash();
				}
				else
				{
					//��~
					Stop = true;
				}
			}
			Old_Pos_X = Old_Pos_X + i;
		}
		//�E
		else if (Direction == 2)
		{
			int i = 0;
			//�Փ˔��肪�ł�܂�
			for (; Stop != true; i++)
			{
				Old_Pos_Y -= 1;//���W��ύX

				//��
				if (Map[Old_Pos_X][Old_Pos_Y] == NOTHING)
				{
//					std::cout << "�G���[:Light" << std::endl;
					//��~
					Stop = true;
				}
				//���
				else if (Map[Old_Pos_X][Old_Pos_Y] == SPACE) {}
				//�S�[��
				else if (Map[Old_Pos_X][Old_Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Old_Pos_X][Old_Pos_Y] == P_DIVER) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�T��
				//else if (Map[Old_Pos_X][Old_Pos_Y] == E_SHARK) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�����}�X
				else if (Map[Old_Pos_X][Old_Pos_Y] == Luminous)
				{
					//��Ԃɕς���
					Map[Old_Pos_X][Old_Pos_Y] = SPACE;
				}
				//����i�E�オ��j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_U)
				{
					//���˂���
					//�@��
					//���^
					Direction = 0;
					Flash();
				}
				//����i��������j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_D)
				{
					//���˂���
					//��
					//�_��
					Direction = 1;
					Flash();
				}
				else
				{
					//��~
					Stop = true;
				}
			}
			Old_Pos_Y = Old_Pos_Y + i;
		}
		//��
		else if (Direction == 3)
		{
			int i = 0;
			//�Փ˔��肪�ł�܂�
			for (; Stop != true; i++)
			{
				Old_Pos_Y += 1;//���W��ύX

				//��
				if (Map[Old_Pos_X][Old_Pos_Y] == NOTHING)
				{
//					std::cout << "�G���[:Light" << std::endl;
					//��~
					Stop = true;
				}
				//���
				else if (Map[Old_Pos_X][Old_Pos_Y] == SPACE) {}
				//�S�[��
				else if (Map[Old_Pos_X][Old_Pos_Y] == GOAL) {}
				//�v���C���[
				//else if (Map[Old_Pos_X][Old_Pos_Y] == P_DIVER) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�T��
				//else if (Map[Old_Pos_X][Old_Pos_Y] == E_SHARK) { Map[Old_Pos_X][Old_Pos_Y] = SPACE; }
				//�����}�X
				else if (Map[Old_Pos_X][Old_Pos_Y] == Luminous)
				{
					//��Ԃɕς���
					Map[Old_Pos_X][Old_Pos_Y] = SPACE;
				}
				//����i�E�オ��j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_U)
				{
					//���˂���
					//�@��
					//���^
					Direction = 1;
					Flash();
				}
				//����i��������j
				else if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_D)
				{
					//���˂���
					//��
					//�_��
					Direction = 0;
					Flash();
				}
				else
				{
					//��~
					Stop = true;
				}
			}
			Old_Pos_Y = Old_Pos_Y - i;

		}
		Stop = false;
	}
}

std::vector<std::vector<int>> Light::MapUpdate()
{
	//���C�g�̍��W���X�V����Ă���Ȃ�
	if (Old_Pos_X != Pos_X || Old_Pos_Y != Pos_Y)
	{
		if (Map[Pos_X][Pos_Y] == MAP_END)
		{
			Map[Pos_X][Pos_Y] = Map[Old_Pos_X][Old_Pos_Y];	//�ړ�����W�Ɉړ��O���W�̃��C�g�i���o�[��}��
			Map[Old_Pos_X][Old_Pos_Y] = MAP_END;	//�}�b�v�[�ɖ߂�
		}
		else
		{
			//�ړ�����폜
			Pos_X = Old_Pos_X;
			Pos_Y = Old_Pos_Y;
		}

		DebugMap();
	}

	return Map;
}

void Light::DebugMap()
{
	std::cout << "�}�b�v�X�V:Light" << std::endl;
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