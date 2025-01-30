//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Kagamidai.h"

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

void Kagamidai::Init()
{

}

std::vector<std::vector<int>> Kagamidai::Update(std::vector<std::vector<int>> MapDate, GameScene& game)
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

void Kagamidai::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
