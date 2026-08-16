#include "DxLib.h"
#include "Game.h"

int WINAPI WinMain
(
    HINSTANCE,
    HINSTANCE,
    LPSTR,
    int
)

{
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetUseLighting(FALSE);
    SetDrawScreen(DX_SCREEN_BACK);

    Game game;

    while (ProcessMessage() == 0 &&
        CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        game.Update();
        game.Draw();

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}