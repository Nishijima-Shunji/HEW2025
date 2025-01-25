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

std::vector<std::vector<int>> Player::Update(std::vector<std::vector<int>> MapData)
{
    Map = MapData;

    SetUp();

    Move();

    // �ҋ@�A�j���[�V����
    SetUV(animcount % 4 , (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
    //�������Ԃ��l���������Ă��Ȃ�
}

void Player::SetUp()//�X�e�[�W�X�V���Ƃɍs��
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (Map[i][j] == P_DIVER)
            {   //�v���C���[��o�^

                MoveList[i][j] = P_DIVER;
                Map[i][j] = NOTHING;

                X = i;
                Y = j;
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
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == TRAP)
            {   //�g���b�v��o�^

                MoveList[i][j] = TRAP;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == STREAM_R)
            {   //�C��(�E)��o�^

                MoveList[i][j] = STREAM_R;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == STREAM_L)
            {   //�C��(��)��o�^

                MoveList[i][j] = STREAM_L;
                Map[i][j] = NOTHING;
            }
            else if (Map[i][j] == MOB_1)
            {   //�I�j�L������o�^

                MoveList[i][j] = MOB_1;
                Map[i][j] = NOTHING;
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

    //�v���C���[�̃}�b�v��̍��W���v�Z
    targetX = pos.x;
    targetY = pos.y;
    //���C�g�Ƃ̐ڐG�m�F
    //�Ǝ˒�
    if (Map[X][Y] == Luminous)
    {
        //���C�g�������m�F
        if (Map[X - 1][Y] == Luminous)
        {
            //�㉺�ړ�
            Vertical = true;
            Horizontal = false;
        }
        else if (Map[X + 1][Y] == Luminous)
        {
            //�㉺�ړ��i��͕ǁj
            Vertical = true;
            Horizontal = false;
        }
        else
        {
            //���E�ړ�
            Vertical = false;
            Horizontal = true;
        }

        //�S�[���ɋ߂������ֈړ�
        if (Vertical == true)
        {
            if (Goal_X > X) //�S�[������ɂ���
            {
                targetY -= 30.0f;
                X += 1;
            }
            else if (Goal_X < X)//�S�[����艺�ɂ���
            {
                targetY += 30.0f;
                X -= 1;
            }
            else// �S�[���Ɠ�������
            {

            }
        }
        else if (Horizontal == true)
        {
            if (Goal_Y > Y) //�S�[����荶�ɂ���
            {
                targetX += 30.0f;
                Y += 1;
            }
            else if (Goal_Y < Y)//�S�[�����E�ɂ���
            {
                targetX -= 30.0f;
                Y -= 1;
            }
            else// �S�[���Ɠ�������
            {

            }
        }
    }
    //��Ǝ�
    else
    {
        Vertical = false;
        Horizontal = false;
    }

    Animation();
}

void Player::Animation()
{
    /*�A�j���[�V����*/
     // ���炩�ɖڕW���W�ֈړ�
    if (std::abs(pos.x - targetX) > 0.01f)
        pos.x += (targetX - pos.x) * speed * deltaTime;
    if (std::abs(pos.y - targetY) > 0.01f)
        pos.y += (targetY - pos.y) * speed * deltaTime;

    //SetPos(pos.x, pos.y, pos.z);
    SetPos(targetX, targetY, pos.z);
}

void Player::DebugList()
{
    std::cout << "�}�b�v�X�V" << std::endl;
    //�f�o�b�O	�}�b�v���l�\��
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            std::cout << MoveList[i][j] << ",";
        }
        std::cout << std::endl;
    }
    //======================
}

//******************************************************************************
//	End of file.
//******************************************************************************
