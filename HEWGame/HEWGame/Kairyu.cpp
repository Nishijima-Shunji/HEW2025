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

//�R���X�g���N�^
//: x(startX), y(startY), targetX(startX), targetY(startY), speed(spd) {}

void Kairyu::Init()
{

}

std::vector<std::vector<int>> Kairyu::Update(std::vector<std::vector<int>> MapDate)
{
    Map = MapDate;

    SetUp();

    Move();

    // �ҋ@�A�j���[�V����
   // SetUV(animcount % 4 , (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
}

void Kairyu::SetUp()//�X�e�[�W�X�V���Ƃɍs��
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 32; j++) {
            if (Map[i][j] == 2)
            {   //�v���C���[��o�^

                //-1�ɂȂ��Ă��邩�甽�����Ȃ�
                MoveList[i][j] = 2;
                Map[i][j] = 0;

                X = i;
                Y = j;
            }
            else if (Map[i][j] == 6)
            {   //�S�[������o�^

                MoveList[i][j] = 6;
                Goal_X = i;
                Goal_Y = j;
            }
            else
            {
                MoveList[i][j] = 0;
            }
        }
    }
}

void Kairyu::Move()
{
    DirectX::XMFLOAT3 pos = GetPos();

    //�v���C���[�̃}�b�v��̍��W���v�Z
    targetX = pos.x;
    targetY = pos.y;
    //���C�g�Ƃ̐ڐG�m�F
    //�Ǝ˒�
    if (Map[X][Y] == 5)
    {
        //���C�g�������m�F
        if (Map[X - 1][Y] == 5)
        {
            //�㉺�ړ�
            Vertical = true;
            Horizontal = false;
        }
        else if (Map[X + 1][Y] == 5)
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

void Kairyu::Animation()
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

void Kairyu::DebugList()
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

void Kairyu::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
