#pragma once
#include <stdio.h>
#include <vector>
#include "Input.h"
#include "Object.h"
#include "TextureManager.h"

class Game;

class BaseScene {
protected:
    Input input;
    std::vector<std::vector<int>> maplist;

public:
    BaseScene();
    virtual ~BaseScene();
    virtual void Update() = 0;
    virtual void Draw() = 0;
};