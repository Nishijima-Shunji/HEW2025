#pragma once
#include "BaseScene.h"

class StageSelectScene : public BaseScene
{
private:
    TextureManager* textureManager;
    std::unique_ptr<Object> select_bg;
    std::unique_ptr<Object> load_bg;
    std::unique_ptr<Object> sensuikan;
    std::vector<std::unique_ptr<Object>> stageicon;
    
    int framecount = 0;
    int nowStage = 1;
    int nextStage = 1;

    int loadstate = 0;

    bool move = false;

public:
    StageSelectScene();
    ~StageSelectScene();


    void Update() override;
    void Draw() override;
};

