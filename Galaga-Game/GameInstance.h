#pragma once
#include "Singleton.h"

class GameInstance final : public StreamEngine::Singleton<GameInstance>
{
public:
	void SetScreenWidth(int width);
	int GetScreenWidth() const;

	void SetScreenHeight(int height);
	int GetScreenHeight() const;

	void SetScreenMinX(int screenMin);
	int GetScreenMinX() const;

	void SetScreenMinY(int screenMin);
	int GetScreenMinY() const;

private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	int m_ScreenMinX{};
	int m_ScreenMinY{};
};
