#include "Player.h"

Player::Player()
{
    pos = VGet(0.0f, 1.0f, 0.0f);
    forward = VGet(0, 0, 1);
    speed = 0.2f;
}

void Player::Update()
{
    if (CheckHitKey(KEY_INPUT_W))
    {
        pos.z = pos.z + speed;
        forward = VGet(0, 0, 1);
    }

    if (CheckHitKey(KEY_INPUT_S))
    {
        pos.z = pos.z - speed;
        forward = VGet(0, 0, -1);
    }

    if (CheckHitKey(KEY_INPUT_A))
    {
        pos.x = pos.x - speed;
        forward = VGet(-1, 0, 0);
    }

    if (CheckHitKey(KEY_INPUT_D))
    {
        pos.x = pos.x + speed;
        forward = VGet(1, 0, 0);
    }
}

void Player::Draw()
{
    DrawSphere3D(
        pos,
        1.5f,
        16,
        GetColor(0, 0, 255),
        GetColor(0, 0, 255),
        TRUE
    );
}

//位置
VECTOR Player::GetPos() const
{
    return pos;
}

//向き
VECTOR Player::GetForward() const
{
    return forward;
}