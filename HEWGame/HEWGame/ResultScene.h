#pragma once
#include "BaseScene.h"


class Game;
class ResultScene : public BaseScene
{
private:
    Object* result_bg;

public:
    ResultScene();
    ~ResultScene();


    void Update() override;
    void Draw() override;
};

