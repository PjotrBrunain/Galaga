#pragma once
#include "BaseComponent.h"

class PlayerBehavior : public StreamEngine::BaseComponent
{
public:
	PlayerBehavior(const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject);
	virtual ~PlayerBehavior() = default;

	void Die();

	PlayerBehavior(const PlayerBehavior&) = delete;
	PlayerBehavior(PlayerBehavior&&) noexcept = delete;
	PlayerBehavior& operator=(const PlayerBehavior&) = delete;
	PlayerBehavior& operator=(PlayerBehavior&&) noexcept = delete;

private:
	bool m_HasDied;
};
