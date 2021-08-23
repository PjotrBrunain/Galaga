#pragma once
#include "Command.h"
#include <memory>

class PlayerBehavior;

class Shoot final : public StreamEngine::Command
{
public:
	explicit Shoot(std::weak_ptr<PlayerBehavior> pActingBehavior);

	void Execute() override;

private:
	std::weak_ptr<PlayerBehavior> m_pActingBehavior;
};
