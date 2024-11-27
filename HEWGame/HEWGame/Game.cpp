#define NOMINMAX

//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include "Game.h"
#include <time.h>
#include <vector>
#include <iostream>

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
void Game::Init(HWND hWnd) {
	srand((unsigned)time(NULL));

	D3D_Create(hWnd);

	//sound.Init();	//サウンドを初期化
	//sound.Play(SOUND_LABEL_BGM000);	//BGMを再生

	//result_bg.Init(L"asset/Result_test.png", 8, 4);
	//result_bg.SetPos(0.0f, 0.0f, 0.0f);	//位置を設定
	//result_bg.SetSize(300.0f, 300.0f, 0.0f);	//大きさを設定
	//result_bg.SetAngle(0.0f);	//角度を設定
	//result_bg.SetColor(1.0f, 1.0f, 1.0f, 1.0f);	//色を設定

	//============================
	//デバッグ
	
	//============================

	//初期シーンをタイトルにする
	sm.ChangeScene(sm.TITLE);

	//マップデータを読み込み
	DataTable = Loadmap("Data/TestData.csv");
}
//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void Game::Draw() {
	// ゲーム処理実行
	D3D_StartRender();
	sm.Render();
	//======================
	//デバッグ	マップ数値表示
	if (a == 0) {
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 32; j++) {

				std::cout << DataTable[i][j] << ",";
			}
			std::cout << std::endl;
		}
		a++;
	}
	//======================
	D3D_FinishRender();
}
//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void Game::Uninit() {
	title_bg.Uninit();			//タイトルを終了
	result_bg.Uninit();			//タイトルを終了

	//sound.Uninit();			//サウンドを終了

	// DirectXの解放処理
	D3D_Release();
}
//==============================================================================
//!	@fn		
//!	@brief	
//!	@param	
//!	@param	
//!	@param	
//!	@param	
//!	@retval 
//==============================================================================
void Game::Update() {
	sm.Update();	//現在シーンのアップデートを実行
}

//******************************************************************************
//	End of file.
//******************************************************************************
