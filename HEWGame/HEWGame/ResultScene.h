#pragma once
#include "BaseScene.h"


class Game;
class ResultScene : public BaseScene
{
private:
    TextureManager* textureManager;
    std::unique_ptr<Object> result_bg;
    std::unique_ptr<Object> board;
    std::unique_ptr<Object> sensuikan;
    std::unique_ptr<Object> button;
    std::vector<std::unique_ptr<Object>> mendako;
    std::vector<std::unique_ptr<Object>> scoreNum;
    std::vector<std::unique_ptr<Object>> timeNum;

    int timescore;
    int Mscore;
    int Score;
    int tempScore = 0;
    int revealIndex = 0;
    int framecount = 0;
    int scoreFixCounter = 0;
    int state = 0;

    // 揺れの設定
    float amplitude = 20.0f;  // 揺れの大きさ
    float frequency = 0.005f;  // 揺れの速さ（Hz）
    float noise = (rand() % 100 - 50) * 0.001f;  // -0.05f 〜 0.05f のランダム値

public:
    ResultScene(int scorem, int Mscore, int time);
    ~ResultScene();

    void Update() override;
    void Draw() override;

    void BgAnimation();
    void SensuikanAnimation();

};

