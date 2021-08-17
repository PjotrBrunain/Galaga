#pragma once
#include "Command.h"
#include <memory>

class Controller;

class MoveRight final : public StreamEngine::Command
{
public:
	explicit MoveRight(std::shared_ptr<Controller> pActingObjectController);

	void Execute() override;

private:
	std::shared_ptr<Controller> m_pActingObjectController;
};