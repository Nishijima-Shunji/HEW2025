#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
#include <chrono>

#include "Light.h"
#include "O2.h"
#define MAXTIME (600000)  //1分
//#define MAXTIME (10000)     //10秒

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> road_bg;
    std::unique_ptr<Object> game_bg;
    std::vector<Object*> game_bg_list;  // オブジェクトのリスト

    int mapval = 0;
    std::vector<std::vector<std::unique_ptr<Object>>> mapdata;
    std::vector<std::unique_ptr<Object>> characterObj;

    std::vector<std::unique_ptr<O2>> cylinder;
    std::vector<std::unique_ptr<O2>> o2;

    //std::vector<std::vector<int>> maplist;

    int WidthMAX = 0;
    int HeightMAX = 0;

    int state = 0;
    int score = 0;
    bool deadFlg = false;

public:

    GameScene(int stage);
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData(int stage);
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);
    std::unique_ptr<Object> DeleteObject(int objectType, TextureManager* textureManager);

    void GetMapSize();

    void o2Gauge(std::chrono::milliseconds time);
};

