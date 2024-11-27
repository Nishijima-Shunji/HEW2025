#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:

    Object* game_bg;

    TextureManager* textureManager;
    std::vector<Object*> game_bg_list;  // オブジェクトのリスト

    int mapval = 0;
    std::vector<std::vector<std::unique_ptr<Object>>> mapdata;
    std::vector<std::vector<int>> maplist;

public:
    GameScene();
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData();
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);
};

