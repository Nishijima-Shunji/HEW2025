#pragma once
#include "BaseScene.h"
#include <vector>

class Game;
class TitleScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> logo;
    Object* title_bg;    // タイトル背景
    Object* title_name;  // タイトル名
    std::vector<std::unique_ptr<Object>> button;    // ボタン
    std::vector<Object*> title_Ob;  // タイトルオブジェクト

    int framecount = 0;
    int state = 0;

    void InitTitleObjects(int count);

public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;
};