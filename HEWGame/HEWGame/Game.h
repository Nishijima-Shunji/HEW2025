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

class Game
{
private:
	Input input;
	Sound sound;
	SceneManager sm;
	int a = 0;

	Light light;
	
public:
	std::vector<std::vector<int>> DataTable;

	Object title_bg;		//�^�C�g���I�u�W�F�N�g
	//Object game_bg;			//�Q�[���I�u�W�F�N�g
	Object result_bg;		//���U���g�I�u�W�F�N�g

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