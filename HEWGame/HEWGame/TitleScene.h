#pragma once
#include "BaseScene.h"
#include <vector>

#include "Cursol.h"
#include "SoundCursol.h"

class Game;
class TitleScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> logo;
    std::unique_ptr<Object> light;
    Object* title_bg;    // �^�C�g���w�i
    Object* title_name;  // �^�C�g����
    
    std::vector<std::unique_ptr<Object>> button;
    std::vector<std::unique_ptr<Object>> window;
    std::vector<std::unique_ptr<Object>> icon;
    std::unique_ptr<Object> setting;
    std::vector<std::unique_ptr<SoundCursol>> sound_cursol;
    std::unique_ptr<Cursol> cursol;
    std::unique_ptr<Object> close;
    std::vector<Object*> title_Ob;  // �^�C�g���I�u�W�F�N�g

    int framecount = 0;
    int state = 0;
    int move = 0;
    int selectButton = 1;
    int nowButton = 1;

    void InitTitleObjects(int count);

public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;

    void InitAnimation();
    void BGanimation();

    void Select(Input* input);
    void OptionSelect(Input* input);
};