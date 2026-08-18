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

    //最初の出現
    spawnInterval = 2000;
    nextSpawn = GetNowCount() + spawnInterval;

    score = 0;

    attackTimer = 0;

    startTime = GetNowCount();
    limitTime = 60;

    //モグラ複数関連
    for (int i = 0; i < 5; i++)
    {
        moles.push_back(Mole());
    }
}

void Game::Update()
{
    player.Update();

    int now = GetNowCount();


    //モグラ出現処理
    if (now > nextSpawn)
    {
        int index;

        //出現可能な穴が見つかるまで繰り返す
        bool canSpawn = false;

        while (!canSpawn)
        {
            //ランダムに穴を選ぶ
            index = GetRand((int)holes.size() - 1);

            canSpawn = true;

            //既にその穴にモグラがいるか確認
            for (auto& mole : moles)
            {
                //非表示のモグラは無視
                if (!mole.IsActive())
                {
                    continue;
                }

                //同じ座標にモグラがいたら出現不可
                if (
                    mole.GetPos().x == holes[index].GetPos().x &&
                    mole.GetPos().z == holes[index].GetPos().z
                    )
                {
                    canSpawn = false;
                    break;
                }
            }
        }

        //空いているモグラを出現させる
        for (auto& mole : moles)
        {
            if (!mole.IsActive())
            {
                mole.Spawn(
                    holes[index].GetPos()
                );

                break;
            }
        }

        //次回の出現時間を設定
        nextSpawn = now + spawnInterval;

        //徐々に出現速度を上げる
        if (spawnInterval > 500)
        {
            spawnInterval -= 50;
        }
    }

    for (auto& mole : moles)
    {
        mole.Update();
    }

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

        for (auto& mole : moles)
        {
            if (!mole.IsActive())
            {
                continue;
            }

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
                score += 100;

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

    //地面横線
    for (int z = -20; z <= 20; z += 5)
    {
        DrawLine3D(
            VGet(-20.0f, 0.0f, (float)z),
            VGet(20.0f, 0.0f, (float)z),
            GetColor(0, 255, 0)
        );
    }

    //地面縦線
    for (int x = -20; x <= 20; x += 5)
    {
        DrawLine3D(
            VGet((float)x, 0.0f, -20.0f),
            VGet((float)x, 0.0f, 20.0f),
            GetColor(0, 255, 0)
        );
    }

    //穴
    for (auto& hole : holes)
    {
        hole.Draw();
    }


    //モグラ
    for (auto& mole : moles)
    {
        mole.Draw();
    }

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