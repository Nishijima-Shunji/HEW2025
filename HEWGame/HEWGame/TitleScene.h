#pragma once
#include "BaseScene.h"
#include <vector>

class Game;
class TitleScene : public BaseScene
{
private:
    Object* title_bg;    // �^�C�g���w�i
    Object* title_name;  // �^�C�g����
    std::vector<Object*> title_Ob;  // �^�C�g���I�u�W�F�N�g

    void InitTitleObjects(int count);

public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;
};