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
//コンストラクタ
Light::Light(){
	Mode = 0;
	Old_Pos_X = 0;
	Old_Pos_Y = 0;
	Pos_X = 0;
	Pos_Y = 0;
	Count = 0;
	Number = 1;

	//←ここまで変数の設定可能
	//lightが定義される前に２回起動（タイトル１回、ゲーム１回）
	//lightが定義された後に１回起動（ゲーム１回）
}
//デストラクタ
Light::~Light() {

}

//
//関数内で変数が定義されると動く
//

void Light::Update(int WidthMAX, int HeightMAX, std::vector<std::vector<int>> MapData)
{
	//引数　：　横幅、高さ、マップデータ
	Width = WidthMAX;
	Height = HeightMAX;
	Map = MapData;

	switch (Mode)
	{
	case 0:
		//ライト切り替え
		//=============================================================================================
		if (input.GetKeyTrigger(VK_Q)) {	//前に戻る
			if (Number != 0)
			{
				Number -= 1;
				Mode++;
			}
		}
		if (input.GetKeyTrigger(VK_E)) {	//次に進む
			if (Number != 0)
			{
				Number += 1;
				Mode++;
			}
		}
		break;
	case 1:
		//座標取得
		//=============================================================================================
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 32; j++) {
				if (MapData[i][j] == 3)
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
		Mode = 0;
		break;
	}

	//移動処理
	//===========================================================================================

	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	if (input.GetKeyTrigger(VK_A)) {
		//縦固定
		if (Pos_Y <= 1) {
			//左レーンに移動
			Pos_Y -= 1;
			Pos_X += 1;
		}
		else {
			Pos_Y -= 1;
		}
	}

}

void Light::Change() {
	//ライト切り替え
//=============================================================================================
	if (input.GetKeyTrigger(VK_Q)) {	//前に戻る
		if (Number != 0)
		{
			Number -= 1;
			Mode++;
		}
	}
	if (input.GetKeyTrigger(VK_E)) {	//次に進む
		if (Number != 0)
		{
			Number += 1;
			Mode++;
		}
	}
}

void Light::Position() {
	//座標取得
//=============================================================================================
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
	Mode = 0;
}

void Light::Move() {

	//移動処理
//===========================================================================================

	Old_Pos_X = Pos_X;
	Old_Pos_Y = Pos_Y;

	//左に移動
	if (input.GetKeyTrigger(VK_A)) {
		//縦固定
		if (Pos_Y <= 1) {
			//左レーンに移動
			Pos_Y -= 1;
			Pos_X += 1;
		}
		else {
			Pos_Y -= 1;
		}
	}
	//右に移動
	if (input.GetKeyTrigger(VK_D)) {
		//縦固定
		if (Pos_Y >= Width - 1) {
			//右レーンに移動
			Pos_Y += 1;
			Pos_X += 1;
		}
		else {
			Pos_Y += 1;
		}
	}

	//上に移動
	if (input.GetKeyTrigger(VK_W)) {
		//縦固定
		if (Pos_X >= 1) {
			Pos_X -= 1;
			Pos_Y += 1;
		}
		else {
			Pos_X -= 1;
		}

	}

	//下に移動
	if (input.GetKeyTrigger(VK_S)) {
		//縦固定
		if (Pos_Y >= Height - 1) {
			Pos_X += 1;
			Pos_Y += 1;
		}
		else {
			Pos_X += 1;
		}
	}
}

void Light::Flash() {

}

std::vector<std::vector<int>> Light::MapUpdate(std::vector<std::vector<int>> MapData)
{
	//マップデータ更新
	//===========================================================================================
	MapData[Old_Pos_X][Old_Pos_Y] = 1;	//壁に戻す
	MapData[Pos_X][Pos_Y] = 3;	//ライトを移動

	return MapData;
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

ライト強度
1：無限
2：５マス
3：３マス
*/