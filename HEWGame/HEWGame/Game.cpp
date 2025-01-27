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

// 静的メンバ変数の定義
HWND Game::test = nullptr;

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

	test = hWnd;
	//============================
	//デバッグ
	
	//============================

	//初期シーンをタイトルにする
	sm.ChangeScene(sm.TITLE);
	//sm.ChangeScene(sm.SELECT);
	//sm.ChangeScene(sm.GAME,2);
	//sm.ChangeScene(sm.RESULT);
	//sm.ChangeScene(sm.RESULT);



	//マップデータを読み込み
	//std::wstring mapPath = L"asset/Data/TestData.csv";
	std::wstring mapPath = L"C:/GitLocal/HEWGame/HEW2025/HEWGame/HEWGame/Data/TestData.csv";
	DataTable = Loadmap(mapPath.c_str());
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
	//if (a == 0) {
	//	for (int i = 0; i < 18; i++) {
	//		for (int j = 0; j < 32; j++) {
	//			std::cout << DataTable[i][j] << ",";
	//		}
	//		std::cout << std::endl;
	//	}
	//	a++;
	//}
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

	//シーンセット
	sm.SetScene();

	sm.Update();	//現在シーンのアップデートを実行
}

HWND GetGameWindowHandle() {
	return Game::GetHANDLE();
}


//******************************************************************************
//	End of file.
//******************************************************************************
