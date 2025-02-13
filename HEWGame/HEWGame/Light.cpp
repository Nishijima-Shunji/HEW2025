//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Light.h"
//#include "Direction.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
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
std::vector<std::vector<int>> Light::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	//マップ情報の更新
	//=============================================================================================
	//マップデータが更新されていたら

	//新しいマップ情報を取得
	Map = MapData;

	return Map;	//MapDate = Map
}
////******************************************************************************
////	End of file.
////******************************************************************************