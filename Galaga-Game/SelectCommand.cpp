#include "stdafx.h"
#include "SelectCommand.h"
#include <utility>

#include "GameInstance.h"
#include "GameObject.h"
#include "PlayerPrefab.h"
#include "SceneManager.h"
#include "SelectComponent.h"

SelectCommand::SelectCommand(std::weak_ptr<StreamEngine::GameObject> selectObject)
	:m_SelectObject(std::move(selectObject))
{
}

void SelectCommand::Execute()
{
	std::shared_ptr<SelectComponent> selectComponent{ m_SelectObject.lock()->GetComponent<SelectComponent>() };
	if (selectComponent != nullptr)
	{
		auto& gameInstance = GameInstance::GetInstance();
		switch (selectComponent->GetSelected())
		{
		case 0:
			gameInstance.SetGameMode(GameMode::SinglePlayer);
			gameInstance.SetPlayer1(CreatePlayer(StreamEngine::SceneManager::GetInstance().GetScene("Level1"), 0, glm::vec3{ 20,0.8f * float(gameInstance.GetScreenHeight()),1 }, 64));
			break;
		case 1:
			gameInstance.SetGameMode(GameMode::Coop);
			gameInstance.SetPlayer1(CreatePlayer(StreamEngine::SceneManager::GetInstance().GetScene("Level1"), 0, glm::vec3{ 20,0.8f * float(gameInstance.GetScreenHeight()),1 }, 64));
			gameInstance.SetPlayer2(CreatePlayer(StreamEngine::SceneManager::GetInstance().GetScene("Level1"), 1, glm::vec3{ gameInstance.GetScreenMinX() + gameInstance.GetScreenWidth() - 20,0.8f * float(gameInstance.GetScreenHeight()),1 }, 64));
			break;
		case 2:
			gameInstance.SetGameMode(GameMode::Versus);
			break;
		default:
			break;
		}
		StreamEngine::SceneManager::GetInstance().SetActiveScene("Level1");
	}
}
