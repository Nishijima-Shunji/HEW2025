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
#include "Bubble.h"

#include "Light.h"

#define XON			(0)
#define YON			(1)

HWND GetGameWindowHandle();


class Game
{
private:
	Input input;
	Sound sound;
	SceneManager sm;

	Light Light;
	
	static HWND test;
public:
	std::vector<std::vector<int>> DataTable;

	void Init(HWND hWnd);
	void Draw();
	void Uninit();
	void Update();

	static HWND GetHANDLE() { return test; };
};

extern Game* _pGame;
//******************************************************************************
//	End of file.
//******************************************************************************