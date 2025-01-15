#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>


#include "Light.h"

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:
    //Light* light;

    Object* game_bg;

    TextureManager* textureManager;
    std::vector<Object*> game_bg_list;  // オブジェクトのリスト

    int mapval = 0;
    std::vector<std::vector<std::unique_ptr<Object>>> mapdata;
    std::vector<std::unique_ptr<Object>> characterObj;
    //std::vector<std::vector<int>> maplist;

    int WidthMAX = 0;
    int HeightMAX = 0;

    int score = 0;

public:

    GameScene(int stage);
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData(int stage);
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);
    std::unique_ptr<Object> DeleteObject(int objectType, TextureManager* textureManager);

    void GetMapSize();
};

