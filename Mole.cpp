#include "Mole.h"

Mole::Mole()
{
    active = false;
    appearTime = 0;
}

void Mole::Spawn(VECTOR p)
{
    pos = p;
    pos.y = 2.0f;

    active = true;
    appearTime = GetNowCount();
}

void Mole::Update()
{
    if (active)
    {
        if (GetNowCount() - appearTime > 1500)
        {
            active = false;
        }
    }
}

void Mole::Draw()
{
    if (!active) return;

    DrawSphere3D(
        pos,
        1.5f,
        16,
        GetColor(139, 69, 19),
        GetColor(139, 69, 19),
        TRUE
    );
}

bool Mole::IsActive() const
{
    return active;
}

void Mole::Hide()
{
    active = false;
}

VECTOR Mole::GetPos() const
{
    return pos;
}