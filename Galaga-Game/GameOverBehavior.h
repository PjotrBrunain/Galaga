#pragma once
#include "BaseComponent.h"

class GameOverBehavior : public StreamEngine::BaseComponent
{
public:
	explicit GameOverBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningObject);
	virtual ~GameOverBehavior() = default;

	void Update(float deltaTime) override;

	void SetRemainingTime(float time);
	static void ResetScenes();

	GameOverBehavior(const GameOverBehavior&) = delete;
	GameOverBehavior(GameOverBehavior&&) noexcept = delete;
	GameOverBehavior& operator=(const GameOverBehavior&) = delete;
	GameOverBehavior& operator=(GameOverBehavior&&) noexcept = delete;

private:
	float m_RemainingTime;
};
