#pragma once
#include "DxLib.h"

class Mole
{
private:
    VECTOR pos;
    bool active;
    int appearTime;

public:
    Mole();

    void Spawn(VECTOR p);
    void Update();
    void Draw();

    bool IsActive() const;
    void Hide();

    VECTOR GetPos() const;
};