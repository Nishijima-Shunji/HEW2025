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
std::vector<std::vector<int>> Light::Update(std::vector<std::vector<int>> MapData, GameScene& game)
{
	input.Update();

	//マップ情報の更新
	//=============================================================================================
	//マップデータが更新されていたら

	//新しいマップ情報を取得
	Map = MapData;
	
	//↓エラー原因：ライトの回数分発生している・移動するたび発生している
	if (SetUp == false)
	{
		Width = 0;
		Height = 0;
		//横幅を取得
		for (int i = 0; i != 32; i++)
		{
			//if (Map[0][i] != NOTHING)
			if (Map[0][i] != -9)
			{
				Width = i;
			}
		}
		//高さを取得
		for (int j = 0; j != 16; j++)
		{
			//if (Map[j][0] != NOTHING)
			if (Map[j][0] != -9)
			{
				Height = j;
			}
		}

		//座標取得
		//===============================================================================================
		Position();

		//ギミック取得
		//===============================================================================================
		SetGimmick();

		SetUp = true;
	}

	

	//ライト切り替え
	//=============================================================================================
	Change();

	//移動処理
	//=============================================================================================
	Move();

	//回転処理
	//=============================================================================================
	Spin();

	//発光処理
	//=============================================================================================
	Flash();

	//マップデータ更新
	//=============================================================================================
	MapUpdate();

	return Map;	//MapDate = Map
}


//ギミックの空白化処理
void Light::SetGimmick()
{
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == WALL)
			{   //壁を登録

				Gimmick[i][j] = WALL;
			}
			else if (Map[i][j] == MIRROR_U)
			{   //鏡鯛（右上がり）を登録

				Gimmick[i][j] = MIRROR_U;
				Map[i][j] = NOTHING;
			}
			else if (Map[i][j] == MIRROR_D)
			{   //鏡鯛（右下がり）を登録

				Gimmick[i][j] = MIRROR_D;
				Map[i][j] = NOTHING;
			}
			else if (Map[i][j] == MOB_2)
			{   //チョウチンアンコウを登録

				Gimmick[i][j] = MOB_2;
				Map[i][j] = NOTHING;
			}
			else
			{
				//	Gimmick[i][j] = SPACE;
			}
		}
	}
}
//ライト切り替え処理
void Light::Change() {
	//ライト切り替え
	//=============================================================================================
	if (input.GetKeyTrigger(VK_Q) || input.GetButtonTrigger(XINPUT_LEFT_SHOULDER)) {	//前に戻る
		if (Number != 1)//ライトの最低登録
		{
			int num = 10000 + (Pos_X * 100 + Pos_Y);
			Lightpos[Number] = num;
			Number--;
			Pos_X = Lightpos[Number] / 100 - 100;
			Pos_Y = Lightpos[Number] % 100;
		}
	}
	if (input.GetKeyTrigger(VK_E) || input.GetButtonTrigger(XINPUT_RIGHT_SHOULDER)) {	//次に進む
		if (Number != LightMAX)//ライトの登録上限
		{
			int num = 10000 + (Pos_X * 100 + Pos_Y);
			Lightpos[Number] = num;
			Number++;
			Pos_X = Lightpos[Number] / 100 - 100;
			Pos_Y = Lightpos[Number] % 100;
		}
	}
}
//座標取得処理
void Light::Position() {
	//座標取得
	//=============================================================================================
	Lightpos.push_back(99999);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 32; j++) {
			if (Map[i][j] == 12 || Map[i][j] == 13 || Map[i][j] == 14 || Map[i][j] == 19)
			{
				int num = 10000 + (i * 100 + j);
				Lightpos.push_back(num);
				LightMAX++;
			}
		}
	}

	Pos_X = Lightpos[Number] / 100 - 100;
	Pos_Y = Lightpos[Number] % 100;
}
//移動処理
void Light::Move() 
{
	//古い座標情報を取得
	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	//上に移動を検知
	if (input.GetKeyTrigger(VK_W) || input.GetButtonTrigger(XINPUT_UP)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_S) || input.GetButtonTrigger(XINPUT_DOWN)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_D) || input.GetButtonTrigger(XINPUT_RIGHT)) {
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
				angle -= 90;
				SetAngle(angle);
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
				angle -= 90;
				SetAngle(angle);
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
	if (input.GetKeyTrigger(VK_A) || input.GetButtonTrigger(XINPUT_LEFT)) {
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
				angle += 90;
				SetAngle(angle);
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
				angle += 90;
				SetAngle(angle);
			}
			//それ以外なら
			else
			{
				Pos_Y -= 1;
			}
		}

		LightOn = false;
	}

}
//回転処理
void Light::Spin()
{
	if (Pos_X != 0 && Pos_X != Height)
	{
		if (Pos_Y != 0 && Pos_Y != Width)
		{
			if (input.GetKeyTrigger(VK_R))
			{
				switch (Direction)
				{
				case 0:
					angle = 270;
					Direction = 2;
					break;
				case 1:
					angle = 90;
					Direction = 3;
					break;
				case 2:
					angle = 180;
					Direction = 1;
					break;
				case 3:
					angle = 0;
					Direction = 0;
					break;
				}
			}
		}
	}

	SetAngle(angle);
}
//発光処理
void Light::Flash() 
{
	//ライトの点灯を検知
	if (input.GetKeyTrigger(VK_SPACE) || input.GetButtonTrigger(XINPUT_A))
	{
		if (Stop == true)
		{
			if (LightOn == true)
			{
				LightOn = false;
			}
			else if (LightOn == false)
			{
				LightOn = true;
			}

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
		}
	}

	if (LightOn == true)
	{
		Stop = false;
		int i = 0;

		switch (Direction)
		{
		case 0://上
			//衝突判定がでるまで
			for (; Stop != true; i++)
			{
				Pos_X += 1;//座標を変更

				FlashSpace();

				FlashGimmick();
			}
			Pos_X = Pos_X - i;
			break;
		case 1://下
			//衝突判定まで発光状態（５）に変える
			for (; Stop != true; i++)
			{
				Pos_X -= 1;

				FlashSpace();

				FlashGimmick();
			}
			Pos_X = Pos_X + i;
			break;
		case 2://右
			//衝突判定まで発光状態（５）に変える
			for (; Stop != true; i++)
			{
				Pos_Y -= 1;

				FlashSpace();

				FlashGimmick();
			}
			Pos_Y = Pos_Y + i;
			break;
		case 3://左
			//衝突判定まで発光状態（５）に変える
			for (; Stop != true; i++)
			{
				Pos_Y += 1;

				FlashSpace();

				FlashGimmick();
			}
			Pos_Y = Pos_Y - i;
			break;
		}
	}
	else if (LightOn == false)
	{
		Stop = false;
		int i = 0;
		switch (Direction)
		{
		case 0://上
			//衝突判定がでるまで
			for (; Stop != true; i++)
			{
				Old_Pos_X += 1;//座標を変更

				FlashSpace();

				FlashGimmick();
			}
			Old_Pos_X = Old_Pos_X - i;
			break;
		case 1://下
			//衝突判定がでるまで
			for (; Stop != true; i++)
			{
				Old_Pos_X -= 1;//座標を変更

				FlashSpace();

				FlashGimmick();
			}
			Old_Pos_X = Old_Pos_X + i;
			break;
		case 2://右
			//衝突判定がでるまで
			for (; Stop != true; i++)
			{
				Old_Pos_Y -= 1;//座標を変更

				FlashSpace();

				FlashGimmick();
			}
			Old_Pos_Y = Old_Pos_Y + i;
			break;
		case 3://左
			//衝突判定がでるまで
			for (; Stop != true; i++)
			{
				Old_Pos_Y += 1;//座標を変更

				FlashSpace();

				FlashGimmick();
			}
			Old_Pos_Y = Old_Pos_Y - i;
			break;
		}
	}
}
//空間に対する発光の判別
void Light::FlashSpace()
{
	if (LightOn == true)
	{
		//暗闇
		if (Map[Pos_X][Pos_Y] == NOTHING)
		{
			Map[Pos_X][Pos_Y] = Luminous; //発光
		}
		//暗闇
		if (Map[Pos_X][Pos_Y] == DARKNESS)
		{
			Map[Pos_X][Pos_Y] = Luminous; //発光
		}
		//空間
		if (Map[Pos_X][Pos_Y] == SPACE)
		{
			Map[Pos_X][Pos_Y] = Luminous; //発光
		}
		//ゴール
		else if (Map[Pos_X][Pos_Y] == GOAL)
		{
			//通過
		}
		//サメ
		else if (Map[Pos_X][Pos_Y] == E_SHARK)
		{
			Map[Pos_X][Pos_Y] = Luminous;
		}
		//発光マス
		else if (Map[Pos_X][Pos_Y] == Luminous)
		{
			//爆発
		}
		//壁/マップ端/ライト
		else
		{
			Stop = true; //停止
		}
	}
	else if (LightOn == false)
	{
		//無
		if (Map[Old_Pos_X][Old_Pos_Y] == NOTHING)
		{
			//std::cout << "エラー:Light" << std::endl;
			Stop = true;	//停止
		}
		//空間
		else if (Map[Old_Pos_X][Old_Pos_Y] == SPACE) 
		{

		}
		//ゴール
		else if (Map[Old_Pos_X][Old_Pos_Y] == GOAL) 
		{

		}
		//発光マス
		else if (Map[Old_Pos_X][Old_Pos_Y] == Luminous)
		{
			//空間に変える
			Map[Old_Pos_X][Old_Pos_Y] = SPACE;
		}
		else
		{
			Stop = true;	//停止
		}
	}
}
//ギミックに対する発光の判別
void Light::FlashGimmick()
{
	if (LightOn == true)
	{
		//鏡鯛
		if (Gimmick[Pos_X][Pos_Y] == MIRROR_U || Gimmick[Pos_X][Pos_Y] == MIRROR_D)
		{
			Reflection(Direction);
			Flash();
		}
		//オニキンメ
		else if (Gimmick[Pos_X][Pos_Y] == MOB_1)
		{
			//
		}
		//アンコウ
		else if (Gimmick[Pos_X][Pos_Y] == MOB_2)
		{
			//
		}
	}
	else if (LightOn == false)
	{
		//鏡鯛
		if (Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_U || Gimmick[Old_Pos_X][Old_Pos_Y] == MIRROR_D)
		{
			Reflection(Direction);
			Flash();
		}
	}
}
//鏡の反射方向
void Light::Reflection(int OldDirection)
{
	//鏡鯛（右上がり
	if (Gimmick[Pos_X][Pos_Y] == MIRROR_U)
	{
		switch (OldDirection)
		{
		case 0:
			Direction = 2;
			break;
		case 1:
			Direction = 3;
			break;
		case 2:
			Direction = 0;
			break;
		case 3:
			Direction = 1;
			break;
		default:
			break;
		}
	}
	//鏡鯛（左下がり
	else if(Gimmick[Pos_X][Pos_Y] == MIRROR_D)
	{
		switch (OldDirection)
		{
		case 0:
			Direction = 3;
			break;
		case 1:
			Direction = 2;
			break;
		case 2:
			Direction = 1;
			break;
		case 3:
			Direction = 0;
			break;
		default:
			break;
		}
	}
}
//マップデータ更新処理
std::vector<std::vector<int>> Light::MapUpdate()
{
	//ライトの座標が更新されているなら
	if (Old_Pos_X != Pos_X || Old_Pos_Y != Pos_Y)
	{
		if (Map[Pos_X][Pos_Y] == MAP_END)
		{
			Map[Pos_X][Pos_Y] = Map[Old_Pos_X][Old_Pos_Y];	//移動先座標に移動前座標のライトナンバーを挿入
			Map[Old_Pos_X][Old_Pos_Y] = MAP_END;	//マップ端に戻す
		}
		else
		{
			//移動先を削除
			Pos_X = Old_Pos_X;
			Pos_Y = Old_Pos_Y;
		}

		DebugMap();
	}

	return Map;
}

void Light::DebugMap()
{
	std::cout << "マップ更新:Light" << std::endl;
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