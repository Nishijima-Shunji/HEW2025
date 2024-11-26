#pragma once
#include "BaseScene.h"
#include <vector>

class Game;
class TitleScene : public BaseScene
{
private:
    Object* title_bg;    // タイトル背景
    Object* title_name;  // タイトル名
    std::vector<Object*> title_Ob;  // タイトルオブジェクト

    void InitTitleObjects(int count);

public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;
};