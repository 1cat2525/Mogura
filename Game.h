#pragma once

#include <vector>

#include "Player.h"
#include "Mole.h"
#include "Hole.h"

class Game
{
private:
    Player player;

    std::vector<Mole> moles;

    std::vector<Hole> holes;

    int nextSpawn;
    int score;

    int attackTimer;

    int startTime;
    int limitTime;

    //出現のやつ、短くね
    int spawnInterval;
public:
    Game();

    void Update();
    void Draw();

    bool IsEnd();
};