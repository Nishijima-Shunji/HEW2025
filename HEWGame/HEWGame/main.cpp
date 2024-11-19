#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

//*****************************************************************************
//!	@file	ファイル名
//!	@brief	簡単な説明
//!	@note	メモ
//!	@author	製作者
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "Game.h"
#include <fstream>

//-----------------------------------------------------------------------------
// マクロの定義
//-----------------------------------------------------------------------------
#define CLASS_NAME   "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "DirectX初期化"// ウィンドウの名前

//-----------------------------------------------------------------------------
// リンクライブラリの設定
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
Game* _pGame;

//==============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	パラメーター
//!	@param	
//!	@param	
//!	@param	
//!	@retval	返り値
//!	@note	
//==============================================================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウクラス情報をまとめる
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	// ウィンドウの情報をまとめる
	HWND hWnd;
	hWnd = CreateWindowEx(0,	// 拡張ウィンドウスタイル
		CLASS_NAME,				// ウィンドウクラスの名前
		WINDOW_NAME,			// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	// ウィンドウスタイル
		CW_USEDEFAULT,			// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,			// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,			// ウィンドウの幅
		SCREEN_HEIGHT,			// ウィンドウの高さ
		NULL,					// 親ウィンドウのハンドル
		NULL,					// メニューハンドルまたは子ウィンドウID
		hInstance,				// インスタンスハンドル
		NULL);					// ウィンドウ作成データ

	//ウィンドウのサイズを修正
	RECT rc1, rc2;
	GetWindowRect(hWnd, &rc1);	//ウィンドウの短径領域を取得
	GetClientRect(hWnd, &rc2);	//クライアントの短径領域を取得
	int sx = SCREEN_WIDTH;
	int sy = SCREEN_HEIGHT;
	sx += ((rc1.right - rc1.left) - (rc2.right - rc2.left));
	sy += ((rc1.bottom - rc1.top) - (rc2.bottom - rc2.top));
	SetWindowPos(hWnd, NULL, 0, 0, sx, sy, (SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE));	//ウィンドウサイズを変更

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);



	_pGame = new Game;
	//ゲーム初期化
	_pGame->Init(hWnd);




	MSG msg;

	//FPS計測用変数
	int fpsCounter = 0;
	long long oldTick = GetTickCount64();	//前回計測時の時間
	long long nowTick = oldTick;	//今回計測時の時間

	//FPS固定用変数
	LARGE_INTEGER liWork;	//workがつく変数は作業用変数
	long long frequency;	//どれくらい細かく時間をカウントできるか
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;
	//時間(単位：カウント)取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;	//前回計測時の時間
	long long nowCount = oldCount;	//今回計測時の時間

#ifdef _DEBUG
	AllocConsole();
	FILE* fp = nullptr;
	freopen_s(&fp, "CON", "w", stdout);
#endif


	//========================================
	//main
	//========================================

	while (1) {
		// 新たにメッセージがあれば
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ウィンドウプロシージャにメッセージを送る
			DispatchMessage(&msg);

			// 「WM_QUIT」メッセージを受け取ったらループを抜ける
			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart;
			//1/60秒が経過したか
			if (nowCount >= oldCount + frequency / 60) {

				_pGame->Update();
				_pGame->Draw();


				fpsCounter++;	//ゲーム処理を実行したら+1する
				oldCount = nowCount;
			}


			nowTick = GetTickCount64();	//現在時間を取得
			//前回計測から1000ミリ秒が経過したか
			if (nowTick >= oldTick + 1000) {
				//FPS表示
				char str[32];
				wsprintfA(str, "FPS=%d", fpsCounter);
				SetWindowTextA(hWnd, str);
				//カウンターリセット
				fpsCounter = 0;
				oldTick = nowTick;
			}
		}
	}
	//ゲーム終了
	_pGame->Uninit();



	UnregisterClass(CLASS_NAME, hInstance);

#ifdef _DEBUG
	FreeConsole();
#endif //_DEBUG



	return (int)msg.wParam;
}


//==============================================================================
//!	@fn		WindowProc
//!	@brief	ウインドウプロシージャ
//!	@param	ウインドウハンドル
//!	@param	メッセージ
//!	@param	Wパラメータ
//!	@param	Lパラメータ
//!	@retval	終了状況
//==============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// 「WM_QUIT」メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // 「x」ボタンが押されたら
	{
		//isMessageBoxShowed = true;	//メッセージボックス表示フラグON
		int res = MessageBoxA(NULL, "終了しますか？", "確認", MB_OKCANCEL);
		//isMessageBoxShowed = false;	//メッセージボックス表示フラグON
		if (res == IDOK) {
			DestroyWindow(hWnd);  // 「WM_DESTROY」メッセージを送る
		}
	}
	break;

	case WM_KEYDOWN: //キー入力があったメッセージ
		if (LOWORD(wParam) == VK_ESCAPE) { //入力されたキーがESCAPEなら
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);//「WM_CLOSE」を送る
		}

	default:
		// 受け取ったメッセージに対してデフォルトの処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}


//******************************************************************************
//	End of file.
//******************************************************************************
