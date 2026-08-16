#pragma once
#include "DxLib.h"

class Hole
{
private:
    VECTOR pos;

public:
    Hole(VECTOR p);

    void Draw();

    VECTOR GetPos() const;
};
