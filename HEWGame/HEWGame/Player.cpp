//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Player.h"
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

std::vector<std::vector<int>> Player::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	Map = MapData;
	if (Start == false)
	{
		SetUp();
		CheckEdge();
		Start = true;
	}

	Move();


	Animation(game);

	// =====�A�j���[�V����=====
	

	return Map;
}

void Player::SetUp()//�X�e�[�W�X�V���Ƃɍs��
{
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == P_DIVER)
			{   //�v���C���[��o�^

				MoveList[i][j] = P_DIVER;
				Map[i][j] = DARKNESS;

				X = i;
				Y = j;
				targetX = pos.x;
				targetY = pos.y;
			}
			else if (Map[i][j] == GOAL)
			{   //�S�[����o�^

				MoveList[i][j] = GOAL;
				Goal_X = i;
				Goal_Y = j;
			}
			else if (Map[i][j] == MENDAKO)
			{   //�����_�R��o�^

				MoveList[i][j] = MENDAKO;
				Map[i][j] = DARKNESS;
			}
			else if (Map[i][j] == TRAP)
			{   //�g���b�v��o�^

				MoveList[i][j] = TRAP;
				Map[i][j] = DARKNESS;
			}
			else if (Map[i][j] == STREAM_R)
			{   //�C��(�E)��o�^

				MoveList[i][j] = STREAM_R;
				Map[i][j] = DARKNESS;
			}
			else if (Map[i][j] == STREAM_L)
			{   //�C��(��)��o�^

				MoveList[i][j] = STREAM_L;
				Map[i][j] = DARKNESS;
			}
			else if (Map[i][j] == MOB_1)
			{   //�I�j�L������o�^

				MoveList[i][j] = MOB_1;
				Map[i][j] = DARKNESS;
			}
			else
			{
				//   MoveList[i][j] = SPACE;
			}
		}
	}
}


void Player::Move()
{
	DirectX::XMFLOAT3 pos = GetPos();

	if (Map[X][Y] == GOAL)
	{
		goalFlg = true;
	}

	if (targetX == pos.x && targetY == pos.y && moveState != 2)//�ړ����������� and �ړ��\���
	{
		//���C�g�Ƃ̐ڐG�m�F
		//�Ǝ˒�
		if (Map[X][Y] == LUMINOUS)
		{
			//�㉺�}�X�̔������m�F
			if (Map[X - 1][Y] == LUMINOUS || Map[X + 1][Y] == LUMINOUS)
			{
				Vertical = true;
			}
			else
			{
				Vertical = false;
			}
			//���E�}�X�̔������m�F
			if (Map[X][Y - 1] == LUMINOUS || Map[X][Y + 1] == LUMINOUS)
			{
				Horizontal = true;
			}
			else
			{
				Horizontal = false;
			}

			//�㉺�ړ�
			if (Vertical == true)
			{
				if (Map[X - 1][Y] != LUMINOUS && Map[X - 1][Y] != GOAL)      //��̃}�X���������Ă��Ȃ�
				{
					Reverse = false;
				}
				else if (Map[X + 1][Y] != LUMINOUS && Map[X + 1][Y] != GOAL) //���̃}�X���������Ă��Ȃ�
				{
					Reverse = true;
				}

				if (Reverse == false)
				{
					targetY -= 30.0f;
					X += 1;
				}
				else if (Reverse == true)
				{
					targetY += 30.0f;
					X -= 1;
				}
			}

			//���E�ړ�
			if (Horizontal == true)
			{
				if (Map[X][Y - 1] != LUMINOUS && Map[X][Y - 1] != GOAL)      //���̃}�X���������Ă��Ȃ�
				{
					Reverse = false;
				}
				else if (Map[X][Y + 1] != LUMINOUS && Map[X][Y + 1] != GOAL) //�E�̃}�X���������Ă��Ȃ�
				{
					Reverse = true;
				}
				if (Reverse == false)
				{
					targetX += 30.0f;
					Y += 1;
				}
				else if (Reverse == true)
				{
					targetX -= 30.0f;
					Y -= 1;
				}
			}
		}
		//��Ǝ�
		else
		{
			Vertical = false;
			Horizontal = false;
			Reverse = false;
		}

	}
	else//�ړ���
	{
		// ���炩�ɖڕW���W�ֈړ�
		//�ڕW���W����ɑ���
		if (pos.x < targetX)
		{
			pos.x += 1.0f;
		}
		//�ڕW���W��艺�ɑ���
		else if (pos.x > targetX)
		{
			pos.x -= 1.0f;
		}
		//�ڕW���W���E�ɑ���
		else if (pos.y > targetY)
		{
			pos.y -= 1.0f;
		}
		//�ڕW���W��荶�ɑ���
		else if (pos.y < targetY)
		{
			pos.y += 1.0f;
		}

		SetPos(pos.x, pos.y, pos.z);
	}
}

void Player::SetMoveState(int _state) {
	moveState = _state;
}

void Player::Animation(GameScene& game) {
	TextureManager* texture = game.GetTexture_ptr();
	// ��Ɉړ�����Ƃ�
	if (Vertical && Reverse) {
		SetTexture(texture, L"asset/survivor2.png", 4, 2);
	}
	// ���Ɉړ�����Ƃ�
	else if (Horizontal) {
		SetTexture(texture, L"asset/survivor1.png", 4, 2);
		if (Reverse) {
			direction = 0;
		}
		else {
			direction = 1;
		}
	}
	// ���� or �ҋ@���
	else {
		SetTexture(texture, L"asset/survivor3.png", 4, 2);
	}
	// �A�j���[�V����
	SetUV(animcount % 4, (animcount / 4) % 2);
	if (framecount % 5 == 0) {
		animcount++;
	}

	framecount++;
}

void Player::CheckEdge()
{
	//�������擾
	for (int i = 0; i < WIDTH; i++) {
		if (Map[0][i] == NODATA) {
			width = i - 1;
			break;
		}
	}
	//�������擾
	for (int j = 0; j < HEIGHT; j++) {
		if (Map[j][0] == NODATA) {
			height = j - 1;
			break;
		}
	}
}

//******************************************************************************
//	End of file.
//******************************************************************************
