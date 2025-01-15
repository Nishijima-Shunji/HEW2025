#pragma once
#include "BaseScene.h"


class Game;
class ResultScene : public BaseScene
{
private:
    Object* result_bg;
    std::vector<std::unique_ptr<Object>> scoreNum;

    int score;
    std::vector<int> scorest;

    int count = 0;
    int state = 0;

public:
    ResultScene(int score);
    ~ResultScene();

    void Update() override;
    void Draw() override;

};

