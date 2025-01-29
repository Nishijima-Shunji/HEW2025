#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
#include <chrono>

#include "Light.h"
#include "O2.h"
#include "Cursol.h"
#include "SoundCursol.h"
#include "Darkness.h"

#define MAXTIME (600000)  //1分
//#define MAXTIME (10000)     //10秒

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> game_bg;
    std::vector<Object*> game_bg_list;  // オブジェクトのリスト
    std::unique_ptr<Object> Mendako_e; //メンダコのエフェクト

    int mapval = 0;
    std::vector<std::vector<std::unique_ptr<Object>>> mapdata;
    std::vector<std::unique_ptr<Object>> characterObj;
    std::vector<std::unique_ptr<Darkness>> darknessObj;

    std::vector<std::unique_ptr<O2>> cylinder;
    std::vector<std::unique_ptr<O2>> o2;
    std::unique_ptr<Object> pause;
    std::vector<std::unique_ptr<Object>> button;
    std::unique_ptr<Object> setting;
    std::vector<std::unique_ptr<SoundCursol>> sound_cursol;
    std::unique_ptr<Cursol> cursol;
    std::unique_ptr<Object> close;

    DirectX::XMFLOAT3 e_pos = {0.0f,0.0f,0.0f};//メンダコエフェクトpos

    //std::vector<std::vector<int>> maplist;

    int WidthMAX = 0;
    int HeightMAX = 0;

    int state = 0;
    int score = 0;
    int stage = 0;
    int mendako = 0;
    bool deadFlg = false;
    int framecount = 0;

    struct ButtonParams {
        float amplitude;  // 揺れの大きさ
        float frequency;  // 揺れの速さ
        float phase;      // ランダムな位相
    };
    // ボタンごとの揺れパラメータを格納する配列
    ButtonParams buttonParams[3];

    DirectX::XMFLOAT3 c_pos;
    bool mendakoAnime_g = false;//メンダコアニメ
    bool menFg = false;//メンダコフラグ
    bool menGk = true;
    int men_Ac = 0;//アニメカウント



public:

    GameScene(int stage);
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData(const int _stage);
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);
    std::unique_ptr<Object> DeleteObject(int objectType, TextureManager* textureManager);

    void CheckDead();
    void CheckAndEraseObject(int i, int j, std::vector<std::unique_ptr<Darkness>>& darknessObj, std::vector<std::vector<int>>& maplist);
    void MapUpdate();
    void PauseSelect(Input* input);
    void PauseAnimation();
    void OptionSelect(Input*);
    void o2Gauge(std::chrono::milliseconds time);
};

