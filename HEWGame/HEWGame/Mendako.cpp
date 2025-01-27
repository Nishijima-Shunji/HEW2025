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
// プロトタイプ宣言
//-----------------------------------------------------------------------------


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

}

std::vector<std::vector<int>> Mendako::Update(std::vector<std::vector<int>> MapDate)
{
    Map = MapDate;

    // 待機アニメーション
    SetUV(animcount % 4 , (animcount / 4) % 2);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
}

//******************************************************************************
//	End of file.
//******************************************************************************
