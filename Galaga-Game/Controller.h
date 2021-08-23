#pragma once
#include "BaseComponent.h"

enum class Shooter;

class Controller final : public StreamEngine::BaseComponent
{
public:
	explicit Controller(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject);
	virtual ~Controller() = default;

	void MoveRight() const;
	void MoveLeft() const;
	void MoveUp() const;
	void MoveDown() const;
	void Shoot(Shooter shooter) const;

	Controller(const Controller&) = delete;
	Controller(Controller&&) noexcept = delete;
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) noexcept = delete;

private:
	const float m_MoveSpeed;
};
