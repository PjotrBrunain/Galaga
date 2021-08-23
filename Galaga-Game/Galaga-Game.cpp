#include "stdafx.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif // _DEBUG

#include "GameInstance.h"
#include "SDL.h"
#include "Stream-Engine.h"
#include "LoadFunction.h"

int main(int, char*[])
{
    constexpr int screenHeight{ 760 };
    constexpr int screenWidth{ 900 };
    constexpr int gameHeight{ 760 };
    constexpr int gameWidth{ 760 };
    StreamEngine::Streamgin engine{};
    GameInstance::GetInstance().SetScreenHeight(gameHeight);
    GameInstance::GetInstance().SetScreenWidth(gameWidth);
    engine.Run(LoadGalagaFunction, screenWidth, screenHeight);
    return 0;
}