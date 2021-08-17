#pragma once
#include "BaseComponent.h"

class Controller final : public StreamEngine::BaseComponent
{
public:
	explicit Controller(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject);
	virtual ~Controller() = default;

	void Update(float deltaTime) override;

	void MoveRight() const;
	void MoveLeft() const;
	void MoveUp() const;
	void MoveDown() const;

	Controller(const Controller&) = delete;
	Controller(Controller&&) noexcept = delete;
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) noexcept = delete;

private:
	const float m_MoveSpeed;
};
