#pragma once
#include "Command.h"
#include <memory>

class Controller;

class MoveLeft final : public StreamEngine::Command
{
public:
	explicit MoveLeft(std::shared_ptr<Controller> pActingObjectController);

	void Execute() override;

private:
	std::shared_ptr<Controller> m_pActingObjectController;
};
