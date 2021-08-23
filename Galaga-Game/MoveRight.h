#pragma once
#include "Command.h"
#include <memory>

class PlayerBehavior;

class MoveRight final : public StreamEngine::Command
{
public:
	explicit MoveRight(std::weak_ptr<PlayerBehavior> pActingObjectController);

	void Execute() override;

private:
	std::weak_ptr<PlayerBehavior> m_pActingObjectController;
};