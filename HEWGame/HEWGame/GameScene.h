#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
#include <chrono>

#include "Light.h"
#include "O2.h"
#include "Cursol.h"
#include "SoundCursol.h"

#define MAXTIME (600000)  //1��
//#define MAXTIME (10000)     //10�b

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> game_bg;
    std::vector<Object*> game_bg_list;  // �I�u�W�F�N�g�̃��X�g

    int mapval = 0;
    std::vector<std::vector<std::unique_ptr<Object>>> mapdata;
    std::vector<std::unique_ptr<Object>> characterObj;

    std::vector<std::unique_ptr<O2>> cylinder;
    std::vector<std::unique_ptr<O2>> o2;
    std::unique_ptr<Object> pause;
    std::vector<std::unique_ptr<Object>> button;
    std::unique_ptr<Object> setting;
    std::vector<std::unique_ptr<SoundCursol>> sound_cursol;
    std::unique_ptr<Cursol> cursol;
    std::unique_ptr<Object> close;

    int WidthMAX = 0;
    int HeightMAX = 0;

    int state = 0;
    int score = 0;
    bool deadFlg = false;
    int framecount = 0;

    struct ButtonParams {
        float amplitude;  // �h��̑傫��
        float frequency;  // �h��̑���
        float phase;      // �����_���Ȉʑ�
    };
    // �{�^�����Ƃ̗h��p�����[�^���i�[����z��
    ButtonParams buttonParams[3];

    DirectX::XMFLOAT3 c_pos;

public:

    GameScene(int stage);
    ~GameScene();

    void Update() override;
    void Draw() override;

    void LoadMapData(int stage);
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);
    std::unique_ptr<Object> DeleteObject(int objectType, TextureManager* textureManager);

    void MapUpdate();
    void PauseSelect(Input* input);
    void PauseAnimation();

    void o2Gauge(std::chrono::milliseconds time);

    void OptionSelect(Input*);
};

