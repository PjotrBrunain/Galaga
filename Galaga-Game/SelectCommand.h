#pragma once
#include <Command.h>
#include <memory>

namespace StreamEngine {
	class GameObject;
}

class SelectCommand : public StreamEngine::Command
{
public:
	explicit SelectCommand(std::weak_ptr<StreamEngine::GameObject> selectObject);
	
	void Execute() override;

private:
	std::weak_ptr<StreamEngine::GameObject> m_SelectObject;
};

