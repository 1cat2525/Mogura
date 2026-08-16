#pragma once

#include <vector>

#include "Player.h"
#include "Mole.h"
#include "Hole.h"

class Game
{
private:
    Player player;
    Mole mole;

    std::vector<Hole> holes;

    int nextSpawn;
    int score;

    int attackTimer;

    int startTime;
    int limitTime;

public:
    Game();

    void Update();
    void Draw();

    bool IsEnd();
};