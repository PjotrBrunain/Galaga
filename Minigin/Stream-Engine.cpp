#include "MiniginPCH.h"
#include "Stream-Engine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "TextureComponent.h"

using namespace std;
using namespace std::chrono;

void StreamEngine::Streamgin::Initialize(const int width, const int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void StreamEngine::Streamgin::LoadGame(const std::function<void()>& loadFunction)
{
	loadFunction();
}

void StreamEngine::Streamgin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void StreamEngine::Streamgin::Run(const std::function<void()>& loadFunction, const int width, const int height)
{
	Initialize(width, height);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");


	LoadGame(loadFunction);

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)  // NOLINT(bugprone-infinite-loop)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = duration<float, std::milli>(currentTime - lastTime).count();
			lastTime = currentTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			lag += deltaTime;
			while (lag >= m_MsPerUpdate)
			{
				sceneManager.FixedUpdate(m_MsPerUpdate);
				lag -= m_MsPerUpdate;
			}
			sceneManager.LateUpdate(deltaTime);
			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
