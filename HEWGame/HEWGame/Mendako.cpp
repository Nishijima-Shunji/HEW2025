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
#include "Input.h"
//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
extern Input input;

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
    menAlive = true;
}

std::vector<std::vector<int>> Mendako::Update(std::vector<std::vector<int>> MapDate)
{

    Map = MapDate;
    if (input.GetKeyTrigger(VK_B))
    {
        Map[1][1] = P_DIVER;
    }
    if (Map[PosY][PosX] == P_DIVER)
    {
        Men_hit = true;
       
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
        if (size.x > 0)
        {
            
            angle += 10.0f;
            size.x -= 1.0f;
            size.y -= 1.0f;
        }
        else
        {
            menAlive = false;
           

        }
    }
    frameCounter++;

    if (!menAlive) {
        Mendako_C++;
        menAlive = true;
        Men_hit = false;
    }
   
}






void Mendako::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
