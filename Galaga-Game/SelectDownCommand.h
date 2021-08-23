#pragma once
#include <Command.h>
#include <memory>

namespace StreamEngine {
	class GameObject;
}

class SelectDownCommand : public StreamEngine::Command
{
public:
	SelectDownCommand(std::weak_ptr<StreamEngine::GameObject> object);
	~SelectDownCommand() override = default;
	
	void Execute() override;
private:
	std::weak_ptr<StreamEngine::GameObject> m_SelectBoardObject;
};

