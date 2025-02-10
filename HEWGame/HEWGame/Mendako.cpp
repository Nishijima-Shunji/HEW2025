//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Mendako.h"

//-----------------------------------------------------------------------------
// グローバル変数
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

//コンストラクタ
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
    // 待機アニメーション

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
