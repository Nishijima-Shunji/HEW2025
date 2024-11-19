#pragma once
#include "BaseScene.h"
#include <memory>

class Game;
class GameScene : public BaseScene
{
private:
    Object* game_bg;

    TextureManager* textureManager;
    std::vector<Object*> game_bg_list;  // �I�u�W�F�N�g�̃��X�g

  int mapval = 0;
    std::vector<std::unique_ptr<Object>> mapdata;
    std::vector<int> maplist;

public:
    GameScene();
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData();
};

