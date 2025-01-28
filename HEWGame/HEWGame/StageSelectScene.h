#pragma once
#include "BaseScene.h"
#include "Bubble.h"
#include "Random.h"

#define ALLRANDOM       (3)
#define BUBBLE_X        (0)
#define BUBBLE_SPEED    (1)
#define BUBBLE_SIZE     (2)

class StageSelectScene : public BaseScene
{
private:
    TextureManager* textureManager;
    std::unique_ptr<Object> select_bg;
    std::unique_ptr<Object> load_bg;
    std::unique_ptr<Object> sensuikan;
    std::vector<std::unique_ptr<Object>> stageicon;
    std::vector<std::unique_ptr<Bubble>> bubble;
    std::unique_ptr<RandomGene> rg[ALLRANDOM];
    
    int framecount = 0;
    int nowStage = 1;
    int nextStage = 1;

    int loadstate = 0;
    int state = 0;

    bool move = false;

public:
    StageSelectScene();
    ~StageSelectScene();


    void Update() override;
    void Draw() override;

    void Select();
    void Load();
    void Move();
    void BG_Animation();
};

