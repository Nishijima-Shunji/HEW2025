#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <memory>
#include <chrono>

#include "Play.h"
#include "Light.h"
#include "O2.h"
#include "Cursol.h"
#include "SoundCursol.h"
#include "Darkness.h"

#define MAXTIME (100000)  // 50�b
//#define MAXTIME (10000)     // 10�b

const int MAP_HEIGHT = 18;
const int MAP_WIDTH = 32;
class Game;
class GameScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> game_bg;
    std::vector<Object*> game_bg_list;  // �I�u�W�F�N�g�̃��X�g
    std::unique_ptr<Object> Mendako_e; //�����_�R�̃G�t�F�N�g
    std::unique_ptr<Object> sensuikan; //�����_�R�̃G�t�F�N�g

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
    std::unique_ptr<Object> control;
    std::unique_ptr<Object> Abutton;

    std::unique_ptr<Object> hold_obj[4];

    DirectX::XMFLOAT3 e_pos = {0.0f,0.0f,0.0f};//�����_�R�G�t�F�N�gpos

    Play play;

    //std::vector<std::vector<int>> maplist;

    int WidthMAX = 0;
    int HeightMAX = 0;

    int state = 0;
    int score = 0;
    int stage = 0;
    bool deadFlg = false;
    bool goalFlg = false;
    int framecount = 0;
    int mendakoScore = 0;
    bool o2Initflg = false;

    struct ButtonParams {
        float amplitude;  // �h��̑傫��
        float frequency;  // �h��̑���
        float phase;      // �����_���Ȉʑ�
    };
    // �{�^�����Ƃ̗h��p�����[�^���i�[����z��
    ButtonParams buttonParams[3];

    DirectX::XMFLOAT3 c_pos;
    bool mendakoAnime_g = false; //�����_�R�A�j��
    //bool menFg = false;//�����_�R�t���O
    bool menGk = true;
    int men_Ac = 0;//�A�j���J�E���g

    void ChangeCamera();

public:

    GameScene(int stage);
    ~GameScene();

    void Update() override;
    void Draw() override;

    std::vector<std::unique_ptr<Object>>& GetCharacterObjects() { return characterObj;}
    TextureManager* GetTexture_ptr() { return textureManager; };

    void LoadMapData(const int _stage);
    std::unique_ptr<Object> CreateObject(int objectType, TextureManager* textureManager);

    void CheckDead();
    void CheckAndEraseObject(int i, int j, std::vector<std::unique_ptr<Darkness>>& darknessObj, std::vector<std::vector<int>>& maplist);
    void MapUpdate();
    void PauseSelect(Input* input);
    void PauseAnimation();
    void OptionSelect(Input*);
    void o2Gauge(std::chrono::milliseconds time);
    void DeadAnimation();
};

