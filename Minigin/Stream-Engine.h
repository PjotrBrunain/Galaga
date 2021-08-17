#pragma once
#include <functional>
struct SDL_Window;
namespace StreamEngine
{
	class Streamgin
	{
	public:
		void Initialize(const int width, const int height);
		static void LoadGame(const std::function<void()>& loadFunction);
		void Cleanup();
		void Run(const std::function<void()>& loadFunction, const int width, const int height);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		float m_MsPerUpdate{ 64.f };
	};
}