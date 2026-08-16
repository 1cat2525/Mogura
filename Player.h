#pragma once
#include "DxLib.h"

class Player
{
private:
    VECTOR pos;
    VECTOR forward;
    float speed;

public:
    Player();

    void Update();
    void Draw();

    VECTOR GetPos() const;
    VECTOR GetForward() const;
};