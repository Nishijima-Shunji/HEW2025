#pragma once
#include "BaseScene.h"
#include <vector>

class Game;
class TitleScene : public BaseScene
{
private:
    TextureManager* textureManager;

    std::unique_ptr<Object> logo;
    Object* title_bg;    // �^�C�g���w�i
    Object* title_name;  // �^�C�g����
    std::vector<std::unique_ptr<Object>> button;    // �{�^��
    std::vector<Object*> title_Ob;  // �^�C�g���I�u�W�F�N�g

    int framecount = 0;
    int state = 0;

    void InitTitleObjects(int count);

public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;
};