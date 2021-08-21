#pragma once
#include <algorithm>

#include "MiniginPCH.h"

#include <fstream>

#include "FPSComponent.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "PlayerPrefab.h"
#include "Scene.h"
#include "ZakoPrefab.h"

inline void TestLoadFunction()
{
	const auto& scene = StreamEngine::SceneManager::GetInstance().CreateScene("Demo");


	std::shared_ptr<StreamEngine::GameObject> fpsCounter{ std::make_shared<StreamEngine::GameObject>() };

	const std::shared_ptr<StreamEngine::TextComponent> pTxtComponent{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",fpsCounter) };
	pTxtComponent->SetSize(26);
	pTxtComponent->SetColor({ 0,255,0,255 });
	const std::shared_ptr<StreamEngine::FPSComponent> pFpsComponent{ std::make_shared<StreamEngine::FPSComponent>(fpsCounter) };
	pTxtComponent->LinkText(pFpsComponent->GetTextLink());
	pTxtComponent->SetDoUpdate(true);

	fpsCounter->AddComponent(pTxtComponent);
	fpsCounter->AddComponent(pFpsComponent);

	fpsCounter->GetTransform().SetPosition(0, 0, 0);

	scene->Add(fpsCounter);

	constexpr float playerSize{ 64 };
	constexpr float margin{ 5 };

	CreatePlayer(scene, 1, glm::vec3{GameInstance::GetInstance().GetScreenMinX() + margin,
		GameInstance::GetInstance().GetScreenMinY() + GameInstance::GetInstance().GetScreenHeight() - playerSize - margin,
		1},
		playerSize);

	CreateZako(scene, glm::vec3{ 0.4f * GameInstance::GetInstance().GetScreenWidth() + GameInstance::GetInstance().GetScreenMinX(),0.2f* GameInstance::GetInstance().GetScreenHeight() + GameInstance::GetInstance().GetScreenMinY(),1 }, 48);

	StreamEngine::SceneManager::GetInstance().SetActiveScene("Demo");
}

inline void ReadLevelFromFile(const std::string& filePath, const std::shared_ptr<StreamEngine::Scene>& scene)
{
	std::ifstream fileStream{ filePath };
	std::string line{};
	if (fileStream)
	{
		do
		{
			std::getline(fileStream, line);
			if (line == "{")
			{
				std::getline(fileStream, line);
				if (line.find("zakos") != std::string::npos)
				{
					do
					{
						std::getline(fileStream, line);
						std::stringstream ss{ line };
						if (line.find("{") != std::string::npos)
						{
							float x{};
							float y{};
							float size{};
							do
							{
								if (line.find("x") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									x = std::stof(line);
								}
								else if (line.find("y") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									y = std::stof(line);
								}
								else if (line.find("size") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									size = std::stof(line);
								}
							}
							while (line.find("}") == std::string::npos);
							CreateZako(scene, glm::vec3{ x,y,1 }, size);
						}
					}
					while (line.find("]") == std::string::npos);
				}
			}
		}
		while (!fileStream.eof());
	}
}