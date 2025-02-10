//*****************************************************************************
//!	@file	�t�@�C����
//!	@brief	�ȒP�Ȑ���
//!	@note	����
//!	@author	�����
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Mendako.h"

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

void Mendako::Init()
{
    //menAlive = true;
}

std::vector<std::vector<int>> Mendako::Update(std::vector<std::vector<int>> MapDate, GameScene& game)
{

    Map = MapDate;

    if (Map[PosY][PosX] == P_DIVER)
    {
        //Men_hit = true;
        if (menAlive) {
            Men_hit = true;
        }
    }
    if (Men_hit)
    {
        Catch();
    }
    // �ҋ@�A�j���[�V����

    SetUV(animcount % 4, (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;
    return Map;
}


void Mendako::Catch()
{
    if (frameCounter % 2 == 0) 
    {
        if (size.x < 35)
        {
            size.x += 1.0f;
            size.y += 1.0f;
            pos.y += 1.0f;
        }
        else {
            size.x = 0.0f;
            size.y = 0.0f;
            menAlive = false;
        }
    }
    frameCounter++;

    if (!menAlive) {
        Mendako_C++;
        Men_hit = false;
    }
   
}


void Mendako::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
