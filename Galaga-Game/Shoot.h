#pragma once
#include "Command.h"
#include <memory>

namespace StreamEngine
{
	class GameObject;
}

class Shoot final : public StreamEngine::Command
{
public:
	explicit Shoot(std::shared_ptr<StreamEngine::GameObject> pActingObject);

	void Execute() override;

private:
	std::shared_ptr<StreamEngine::GameObject> m_pActingObject;
};
