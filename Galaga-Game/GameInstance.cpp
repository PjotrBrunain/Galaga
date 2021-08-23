#include "stdafx.h"
#include "GameInstance.h"
#include "Enums.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"

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
	StreamEngine::SceneManager::GetInstance().GetScene("Level1")->GetObjectByName("pointsText")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(m_Points));
	StreamEngine::SceneManager::GetInstance().GetScene("Level2")->GetObjectByName("pointsText")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(m_Points));
	StreamEngine::SceneManager::GetInstance().GetScene("Level3")->GetObjectByName("pointsText")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(m_Points));
}

void GameInstance::SubtractPoints(int points)
{
	m_Points -= points;
}

int GameInstance::GetPoints() const
{
	return m_Points;
}

int GameInstance::GetLives(const Player& player) const
{
	switch (player)
	{
	case Player::P1: return m_P1Lives;
	case Player::P2: return m_P2Lives;
	}
	return 0;
}

bool GameInstance::RemoveLife(const Player& player)
{
	switch (player)
	{
	case Player::P1: 
		--m_P1Lives;
		if (m_P1Lives <= 0) return false;
		break;
	case Player::P2: 
		--m_P2Lives;
		if (m_P2Lives <= 0) return false;
		break;
	}
	return true;
}

void GameInstance::SetGameMode(const GameMode& gameMode)
{
	m_GameMode = gameMode;
}

GameMode GameInstance::GetGameMode() const
{
	return m_GameMode;
}

void GameInstance::SetPlayer1(const std::weak_ptr<StreamEngine::GameObject>& player1)
{
	m_pPlayer1 = player1;
}

void GameInstance::SetPlayer2(const std::weak_ptr<StreamEngine::GameObject>& player2)
{
	m_pPlayer2 = player2;
}

void GameInstance::AddShotFired()
{
	m_ShotsFired++;
}

void GameInstance::AddHit()
{
	m_NumberOfHits++;
}

int GameInstance::GetShotsFired() const
{
	return m_ShotsFired;
}

int GameInstance::GetHits() const
{
	return m_NumberOfHits;
}
