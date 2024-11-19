#pragma once
#include "BaseScene.h"

class Game;
class TitleScene : public BaseScene
{
private:
	Object* title_bg;

public:
	TitleScene();
	~TitleScene();

	void Update() override;
	void Draw() override;
};