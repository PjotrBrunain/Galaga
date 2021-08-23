#pragma once
#include "Command.h"
#include <memory>

class PlayerBehavior;

class MoveLeft final : public StreamEngine::Command
{
public:
	explicit MoveLeft(std::weak_ptr<PlayerBehavior> pActingObjectController);

	void Execute() override;

private:
	std::weak_ptr<PlayerBehavior> m_pActingObjectController;
};
