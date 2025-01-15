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
#include "Input.h"
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Input input;

//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
std::vector<std::vector<int>> Light::Update(std::vector<std::vector<int>> MapDate)
{
	input.Update();

	//マップ情報の更新
	//=============================================================================================
	//マップデータが更新されていたら

	if (Map != MapDate)
	{
		//新しいマップ情報を取得
		Map = MapDate;

		Width = 0;
		Height = 0;
		//横幅を取得
		for (int i = 0; i != 32; i++)
		{
			if (Map[0][i] != -1)
			{
				Width = i;
			}
		}
		//高さを取得
		for (int j = 0; j != 16; j++)
		{
			if (Map[j][0] != 0)
			{
				Height = j;
			}
		}
	}

	//座標取得
	//=============================================================================================
	Position();

	//ライト切り替え
	//=============================================================================================
	Change();

	//移動処理
	//=============================================================================================
	Move();

	return Map;	//MapDate = Map
}

void Light::Change() {
	//ライト切り替え
	//=============================================================================================
	if (input.GetKeyTrigger(VK_Q)) {	//前に戻る
		if (Number != 0)
		{
			Number -= 1;
		}
	}
	if (input.GetKeyTrigger(VK_E)) {	//次に進む
		if (Number != 0)
		{
			Number += 1;
		}
	}
}

void Light::Position() {
	//座標取得
	//=============================================================================================
	Lightpos_X.clear();
	Lightpos_Y.clear();

	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == 3)
			{
				Lightpos_X.push_back(i);
				Lightpos_Y.push_back(j);
			}
		}
	}
	//X座標リストのN番目の数字を取得
	Count = 0;
	for (auto i = Lightpos_X.begin(); i != Lightpos_X.end(); i++)
	{
		if (Count == Number)
		{
			Pos_X = *i;
		}
		Count++;
	}
	//Y座標リストのN番目の数字を取得
	Count = 0;
	for (auto i = Lightpos_Y.begin(); i != Lightpos_Y.end(); i++)
	{
		if (Count == Number)
		{
			Pos_Y = *i;
		}
		Count++;
	}
}

void Light::Move() {
	//移動処理
	//=============================================================================================

	//古い座標情報を取得
	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	//上に移動を検知
	if (input.GetKeyTrigger(VK_W)) {
		//右レーンに存在
		if (Pos_Y == Width)
		{
			//ライト方向→右
			Direction = 2;

			//上端にいる
			if (Pos_X == 1)
			{
				//上部レーンに移動
				Pos_X -= 1;
				//左に１マスずれる
				Pos_Y -= 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_X -= 1;
			}
		}
		//左レーンに存在
		else if (Pos_Y == 0)
		{
			//ライト方向→左
			Direction = 3;

			//上端にいる
			if (Pos_X == 1)
			{
				//上部レーンに移動
				Pos_X -= 1;
				//右に１マスずれる
				Pos_Y += 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_X -= 1;
			}
		}

		LightOn = false;
	}

	//下に移動を検知
	if (input.GetKeyTrigger(VK_S)) {
		//右レーンに存在
		if (Pos_Y == Width)
		{
			//ライト方向→右
			Direction = 2;

			//下端にいる
			if (Pos_X == Height - 1)
			{
				//下部レーンに移動
				Pos_X += 1;
				//左に１マスずれる
				Pos_Y -= 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_X += 1;
			}
		}
		//左レーンに存在
		else if (Pos_Y == 0)
		{
			//ライト方向→左
			Direction = 3;

			//下端にいる
			if (Pos_X == Height - 1)
			{
				//下部レーンに移動
				Pos_X += 1;
				//右に１マスずれる
				Pos_Y += 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_X += 1;
			}
		}

		LightOn = false;
	}

	//右に移動を検知
	if (input.GetKeyTrigger(VK_D)) {
		//上部レーンに存在
		if (Pos_X == 0)
		{
			//ライト方向→上
			Direction = 0;

			//右端にいる
			if (Pos_Y == Width - 1)
			{
				//右レーンに移動
				Pos_Y += 1;
				//１マス下がる
				Pos_X += 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_Y += 1;
			}
		}
		//下部レーンに存在
		else if (Pos_X == Height)
		{
			//ライト方向→下
			Direction = 1;

			//右端にいる
			if (Pos_Y == Width - 1)
			{
				//右レーンに移動
				Pos_Y += 1;
				//１マス上がる
				Pos_X -= 1;
				//90度回転
				SetAngle(270);
			}
			//それ以外なら
			else
			{
				Pos_Y += 1;
			}
		}

		LightOn = false;
	}

	//左に移動を検知
	if (input.GetKeyTrigger(VK_A)) {
		//上部レーンに存在
		if (Pos_X == 0)
		{
			//ライト方向→上
			Direction = 0;

			//左端にいるなら
			if (Pos_Y == 1)
			{
				//左レーンに移動
				Pos_Y -= 1;
				//１マス下がる
				Pos_X += 1;
				//90度回転
				SetAngle(90);
			}
			//それ以外なら
			else
			{
				Pos_Y -= 1;
			}
		}
		//下部レーンに存在
		else if (Pos_X == Height)
		{
			//ライト方向→下
			Direction = 1;

			//左端にいるなら
			if (Pos_Y == 1)
			{
				//左レーンに移動
				Pos_Y -= 1;
				//１マス上がる
				Pos_X -= 1;
				//90度回転
				SetAngle(90);
			}
			//それ以外なら
			else
			{
				Pos_Y -= 1;
			}
		}

		LightOn = false;
	}


	//ライトの点灯を検知
	if (input.GetKeyTrigger(VK_SPACE))
	{
		if (LightOn == true)
		{
			LightOn = false;
		}
		else if (LightOn == false)
		{
			LightOn = true;
		}
		Flash();
	}


	//ライトの座標が更新されているなら
	if (Old_Pos_X != Pos_X || Old_Pos_Y != Pos_Y)
	{
		Flash();
		MapUpdate();
	}

}

void Light::Flash() {
	//発光処理
	//=============================================================================================
	if (LightOn == true)
	{
		if (Pos_X == 0)
		{
			Direction = 0;
		}
		else if (Pos_X == Height)
		{
			Direction = 1;
		}
		else if (Pos_Y == Width)
		{
			Direction = 2;
		}
		else if (Pos_Y == 0)
		{
			Direction = 3;
		}

		//上
		if (Direction == 0)
		{
			//衝突判定まで発光状態（５）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが無（0）なら
				if (Map[Pos_X + i][Pos_Y] == 0)
				{
					//発光状態（５）に変える
					Map[Pos_X + i][Pos_Y] = 5;
				}
				//次のマスが壁（1）なら
				else if (Map[Pos_X + i][Pos_Y] == 1)
				{
					//停止
					Stop = true;
				}
				//次のマスが発光状態（５）なら
				else if (Map[Pos_X + i][Pos_Y] == 5)
				{
					//爆発
				}
			}
		}
		//下
		else if (Direction == 1)
		{
			//衝突判定まで発光状態（５）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが無（0）なら
				if (Map[Pos_X - i][Pos_Y] == 0)
				{
					//発光状態（５）に変える
					Map[Pos_X - i][Pos_Y] = 5;
				}
				//次のマスが壁（1）なら
				else if (Map[Pos_X - i][Pos_Y] == 1)
				{
					//停止
					Stop = true;
				}
				//次のマスが発光状態（５）なら
				else if (Map[Pos_X - i][Pos_Y] == 5)
				{
					//爆発
				}
			}
		}
		//右
		else if (Direction == 2)
		{
			//衝突判定まで発光状態（５）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが無（0）なら
				if (Map[Pos_X][Pos_Y - i] == 0)
				{
					//発光状態（５）に変える
					Map[Pos_X][Pos_Y - i] = 5;
				}
				//次のマスが壁（1）なら
				else if (Map[Pos_X][Pos_Y - i] == 1)
				{
					//停止
					Stop = true;
				}
				//次のマスが発光状態（５）なら
				else if (Map[Pos_X][Pos_Y - i] == 5)
				{
					//爆発
				}
			}
		}
		//左
		else if (Direction == 3)
		{
			//衝突判定まで発光状態（５）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが無（0）なら
				if (Map[Pos_X][Pos_Y + i] == 0)
				{
					//発光状態（５）に変える
					Map[Pos_X][Pos_Y + i] = 5;
				}
				//次のマスが壁（1）なら
				else if (Map[Pos_X][Pos_Y + i] == 1)
				{
					//停止
					Stop = true;
				}
				//次のマスが発光状態（５）なら
				else if (Map[Pos_X][Pos_Y + i] == 5)
				{
					//爆発
				}
			}
		}
	}
	else if (LightOn == false)
	{
		Stop = false;

		//上
		if (Direction == 0)
		{
			//衝突判定までに無（0）変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが発光状態（５）なら
				if (Map[Old_Pos_X + i][Old_Pos_Y] == 5)
				{
					//無（0）に変える
					Map[Old_Pos_X + i][Old_Pos_Y] = 0;
				}
				//次のマスが壁（1）なら
				else if (Map[Old_Pos_X + i][Old_Pos_Y] == 1)
				{
					//停止
					Stop = true;
				}
			}
		}
		//下
		else if (Direction == 1)
		{
			//衝突判定まで無（0）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが発光状態（５）なら
				if (Map[Old_Pos_X - i][Old_Pos_Y] == 5)
				{
					//無（0）に変える
					Map[Old_Pos_X - i][Old_Pos_Y] = 0;
				}
				//次のマスが壁（1）なら
				else if (Map[Old_Pos_X - i][Old_Pos_Y] == 1)
				{
					//停止
					Stop = true;
				}
			}
		}
		//右
		else if (Direction == 2)
		{
			//衝突判定まで無（0）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが発光状態（５）なら
				if (Map[Old_Pos_X][Old_Pos_Y - i] == 5)
				{
					//無（0）に変える
					Map[Old_Pos_X][Old_Pos_Y - i] = 0;
				}
				//次のマスが壁（1）なら
				else if (Map[Old_Pos_X][Old_Pos_Y - i] == 1)
				{
					//停止
					Stop = true;
				}
			}
		}
		//左
		else if (Direction == 3)
		{
			//衝突判定まで無（0）に変える
			for (int i = 1; Stop != true; i++)
			{
				//次のマスが発光状態（５）なら
				if (Map[Old_Pos_X][Old_Pos_Y + i] == 5)
				{
					//無（0）に変える
					Map[Old_Pos_X][Old_Pos_Y + i] = 0;
				}
				//次のマスが壁（1）なら
				else if (Map[Old_Pos_X][Old_Pos_Y + i] == 1)
				{
					//停止
					Stop = true;
				}
			}
		}
		Stop = false;
	}
}

std::vector<std::vector<int>> Light::MapUpdate()
{
	//マップデータ更新
	//=============================================================================================
	Map[Old_Pos_X][Old_Pos_Y] = 1;	//壁に戻す
	Map[Pos_X][Pos_Y] = 3;	//ライトを移動
	//DebugMap();
	return Map;
}

void Light::DebugMap()
{
	std::cout << "マップ更新" << std::endl;
	//デバッグ	マップ数値表示
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			std::cout << Map[i][j] << ",";
		}
		std::cout << std::endl;
	}
	//======================
}

//******************************************************************************
//	End of file.
//******************************************************************************

/*
18×32

何もない
暗闇状態	100
発光状態	200
点灯状態	300

壁
ライト
プレイヤー
エネミー

ライト強度
1：無限
2：５マス
3：３マス
*/