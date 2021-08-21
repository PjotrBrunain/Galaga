#include "GameInstance.h"

void GameInstance::SetScreenWidth(int width)
{
	m_ScreenWidth = width;
}

int GameInstance::GetScreenWidth() const
{
	return m_ScreenWidth;
}

void GameInstance::SetScreenHeight(int height)
{
	m_ScreenHeight = height;
}

int GameInstance::GetScreenHeight() const
{
	return m_ScreenHeight;
}

void GameInstance::SetScreenMinX(int screenMin)
{
	m_ScreenMinX = screenMin;
}

int GameInstance::GetScreenMinX() const
{
	return m_ScreenMinX;
}

void GameInstance::SetScreenMinY(int screenMin)
{
	m_ScreenMinY = screenMin;
}

int GameInstance::GetScreenMinY() const
{
	return m_ScreenMinY;
}

void GameInstance::AddPoints(int points)
{
	m_Points += points;
}

void GameInstance::SubtractPoints(int points)
{
	m_Points -= points;
}

int GameInstance::GetPoints() const
{
	return m_Points;
}
