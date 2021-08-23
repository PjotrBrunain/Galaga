#pragma once
#include "BaseComponent.h"
#include "Controller.h"
#include "Enums.h"

class PlayerBehavior : public StreamEngine::BaseComponent
{
public:
	PlayerBehavior(const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject, Player player, std::weak_ptr<Controller> pController);
	virtual ~PlayerBehavior() = default;

	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void Die();

	void MoveRight() const;
	void MoveLeft() const;
	void Shoot(Shooter shooter) const;

	PlayerBehavior(const PlayerBehavior&) = delete;
	PlayerBehavior(PlayerBehavior&&) noexcept = delete;
	PlayerBehavior& operator=(const PlayerBehavior&) = delete;
	PlayerBehavior& operator=(PlayerBehavior&&) noexcept = delete;

private:
	bool m_HasDied;
	float m_DeadTime;

	Player m_Player;
	std::weak_ptr<Controller> m_pController;
};
