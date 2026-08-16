#include "Game.h"
#include "DxLib.h"
#include <cmath>

Game::Game()
{
    for (int z = 0; z < 3; z++)
    {
        for (int x = 0; x < 3; x++)
        {
            holes.push_back(
                Hole(
                    VGet(
                        (x - 1) * 15.0f,
                        0.0f,
                        (z - 1) * 15.0f
                    )
                )
            );
        }
    }

    nextSpawn = GetNowCount() + 1000;

    score = 0;

    attackTimer = 0;

    startTime = GetNowCount();
    limitTime = 60;
}

void Game::Update()
{
    player.Update();

    int now = GetNowCount();

    //モグラ出現
    if (now > nextSpawn && !mole.IsActive())
    {
        int index = GetRand((int)holes.size() - 1);

        mole.Spawn(
            holes[index].GetPos()
        );

        nextSpawn = now + 2000;
    }

    mole.Update();

    VECTOR attackPos =
        VAdd(
            player.GetPos(),
            VScale(
                player.GetForward(),
                5.0f
            )
        );

    static int oldSpace = 0;

    int space =
        CheckHitKey(KEY_INPUT_SPACE);

    if (space && !oldSpace)
    {
        attackTimer = 15;

        if (mole.IsActive())
        {
            VECTOR molePos =
                mole.GetPos();

            float dx =
                attackPos.x -
                molePos.x;

            float dz =
                attackPos.z -
                molePos.z;

            float dist =
                sqrtf(
                    dx * dx +
                    dz * dz
                );

            if (dist < 3.0f)
            {
                score = score + 100;

                mole.Hide();
            }
        }
    }

    oldSpace = space;

    if (attackTimer > 0)
    {
        attackTimer--;
    }
}

void Game::Draw()
{
    int remain =
        limitTime -
        (GetNowCount() - startTime) / 1000;

    //ゲーム終了
    if (remain <= 0)
    {
        DrawFormatString(
            500,
            300,
            GetColor(255, 0, 0),
            "GAME OVER"
        );

        DrawFormatString(
            500,
            350,
            GetColor(255, 255, 255),
            "SCORE : %d",
            score
        );

        return;
    }

    //カメラ
    SetCameraPositionAndTarget_UpVecY(
        VGet(
            0.0f,
            50.0f,
            -15.0f
        ),
        VGet(
            0.0f,
            0.0f,
            0.0f
        )
    );

    //地面
    for (int z = -20; z <= 20; z += 5)
    {
        DrawLine3D(
            VGet(-20, 0, z),
            VGet(20, 0, z),
            GetColor(0, 255, 0)
        );
    }

    for (int x = -20; x <= 20; x += 5)
    {
        DrawLine3D(
            VGet(x, 0, -20),
            VGet(x, 0, 20),
            GetColor(0, 255, 0)
        );
    }

    //穴
    for (auto& hole : holes)
    {
        hole.Draw();
    }


    //モグラ
    mole.Draw();

    //プレイヤー
    player.Draw();

    //攻撃範囲
    if (attackTimer > 0)
    {
        VECTOR attackPos =
            VAdd(
                player.GetPos(),
                VScale(
                    player.GetForward(),
                    5.0f
                )
            );

        DrawSphere3D(
            attackPos,
            2.5f,
            16,
            GetColor(255, 0, 0),
            GetColor(255, 0, 0),
            FALSE
        );
    }

    //UI
    DrawFormatString(
        20,
        20,
        GetColor(255, 255, 255),
        "TIME : %d",
        remain
    );

    DrawFormatString(
        20,
        50,
        GetColor(255, 255, 0),
        "SCORE : %d",
        score
    );
}

bool Game::IsEnd()
{
    return false;
}