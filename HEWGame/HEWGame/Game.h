//*****************************************************************************
//!	@file	game.h
//!	@brief	
//!	@note	
//!	@author
//*****************************************************************************
#pragma once
#include "Object.h"
#include "input.h"
#include "Sound.h"
#include "SceneManager.h"
#include "mapfile.h"

#include "Light.h"

#define XON			(0)
#define YON			(1)


class Game
{
private:
	Input input;
	Sound sound;
	SceneManager sm;
	int a = 0;

	Light Light;
	
public:
	std::vector<std::vector<int>> DataTable;

	Object title_bg;		//タイトルオブジェクト
	//Object game_bg;			//ゲームオブジェクト
	Object result_bg;		//リザルトオブジェクト

	Object map_0;
	Object map_1;
	Object map_2;


	void Init(HWND hWnd);
	void Draw();
	void Uninit();
	void Update();

};

extern Game* _pGame;
//******************************************************************************
//	End of file.
//******************************************************************************