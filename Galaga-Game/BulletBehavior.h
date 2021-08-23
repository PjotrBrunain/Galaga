#pragma once
#include "BaseComponent.h"
#include "Enums.h"

class BulletBehavior final : public StreamEngine::BaseComponent
{
public:
	explicit BulletBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject, Shooter shooter);
	virtual ~BulletBehavior() = default;

	void Update(float deltaTime) override;

	void Die() const;

	BulletBehavior(const BulletBehavior&) = delete;
	BulletBehavior(BulletBehavior&&) noexcept = delete;
	BulletBehavior& operator=(const BulletBehavior&) = delete;
	BulletBehavior& operator=(BulletBehavior&&) noexcept = delete;
private:
	float m_Speed;
	Shooter m_Shooter;
};
