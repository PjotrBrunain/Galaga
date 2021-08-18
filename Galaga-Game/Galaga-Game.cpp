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
    constexpr int screenWidth{ 760 };
    StreamEngine::Streamgin engine{};
    GameInstance::GetInstance().SetScreenHeight(screenHeight);
    GameInstance::GetInstance().SetScreenWidth(screenWidth);
    engine.Run(TestLoadFunction, screenWidth, screenHeight);
    return 0;
}