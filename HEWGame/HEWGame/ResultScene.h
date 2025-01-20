#pragma once
#include "BaseScene.h"


class Game;
class ResultScene : public BaseScene
{
private:
    Object* result_bg;
    std::vector<std::unique_ptr<Object>> scoreNum;

    int Score;
    int tempScore;
    int revealIndex = 0;
    int count = 0;
    int state = 0;

public:
    ResultScene(int score);
    ~ResultScene();

    void Update() override;
    void Draw() override;

};

