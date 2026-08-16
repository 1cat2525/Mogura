#include "Hole.h"

Hole::Hole(VECTOR p)
{
    pos = p;
}

void Hole::Draw()
{
    DrawSphere3D(
        pos,
        1.5f,
        16,
        GetColor(50, 50, 50),
        GetColor(50, 50, 50),
        TRUE
    );
}

VECTOR Hole::GetPos() const
{
    return pos;
}