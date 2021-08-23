#pragma once
#include <memory>

#include "Enums.h"
#include "GameObject.h"
#include "Singleton.h"

enum class Player;

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

	void AddPoints(int points);
	void SubtractPoints(int points);

	int GetPoints() const;

	int GetLives(const Player& player) const;

	bool RemoveLife(const Player& player);

	void SetGameMode(const GameMode& gameMode);

	GameMode GetGameMode() const;

	void SetPlayer1(const std::weak_ptr<StreamEngine::GameObject>& player1);
	void SetPlayer2(const std::weak_ptr<StreamEngine::GameObject>& player2);

	void AddShotFired();
	void AddHit();
	int GetShotsFired() const;
	int GetHits() const;
private:
	int m_ScreenWidth{};
	int m_ScreenHeight{};
	int m_ScreenMinX{};
	int m_ScreenMinY{};

	int m_Points{};

	int m_P1Lives{3};
	int m_P2Lives{3};

	GameMode m_GameMode{};

	std::weak_ptr<StreamEngine::GameObject> m_pPlayer1{};
	std::weak_ptr<StreamEngine::GameObject> m_pPlayer2{};

	int m_ShotsFired{};
	int m_NumberOfHits{};
};
