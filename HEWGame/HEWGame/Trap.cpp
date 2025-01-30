//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Trap.h"

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

void Trap::Init()
{

}

std::vector<std::vector<int>> Trap::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
    Map = MapData;

    // 待機アニメーション
    SetUV(animcount % 1 , (animcount / 1) % 1);
    if (framecount % 5 == 0) {
        animcount++;
    }

    framecount++;

    return Map;
}

void Trap::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
