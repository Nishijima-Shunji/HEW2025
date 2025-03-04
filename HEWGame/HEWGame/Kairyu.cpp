//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Kairyu.h"
#include "GameScene.h"

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

void Kairyu::Init()
{

}

//void  Kairyu::Update(GameScene* game)
std::vector<std::vector<int>> Kairyu::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	Map = MapData;
	// GameScene から characterObj を取得
	auto& characterObj = game.GetCharacterObjects(); // 参照を使う

	for (const auto& obj : characterObj) {
		// Player オブジェクトかどうかを確認
		Player* player = dynamic_cast<Player*>(obj.get());
		if (player) {
			float deltaX = 0.0f;
			if (this->CheckCollision(*player)) {
				// 右
				if (direction == 0) {
					deltaX = 1.0f;
				}
				// 左
				else if (direction == 1) {
					deltaX = -1.0f;
				}

				// プレイヤーの位置を更新
				player->SetPos(player->GetPos().x + deltaX, player->GetPos().y, 0.0f);

				break; // ループを終了
			}
		}
	}
		// 待機アニメーション
	SetUV(animcount % 4, (animcount / 4) % 2);
	if (framecount % 5 == 0) {
		animcount++;
	}

	framecount++;
	return Map;
}

void Kairyu::Uninit()
{

}

//******************************************************************************
//	End of file.
//******************************************************************************
