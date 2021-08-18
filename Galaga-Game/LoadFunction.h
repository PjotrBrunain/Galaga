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

	//std::shared_ptr<StreamEngine::GameObject> background{ std::make_shared<StreamEngine::GameObject>() };

	//background->AddComponent(std::make_shared<StreamEngine::TextureComponent>("background.jpg", background));

	//scene->Add(background);

	//std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>() };

	//logo->AddComponent(std::make_shared<StreamEngine::TextureComponent>("logo.png", logo));
	//logo->GetTransform().SetPosition(216, 180, 0);

	//scene->Add(logo);

	//std::shared_ptr<StreamEngine::GameObject> text{ std::make_shared<StreamEngine::GameObject>() };

	//text->AddComponent(std::make_shared<StreamEngine::TextComponent>("Lingua.otf", text));

	//text->GetTransform().SetPosition(80, 20, 0);

	//text->GetComponent<StreamEngine::TextComponent>()->SetText("Programming 4 Assignment");

	//text->GetComponent<StreamEngine::TextComponent>()->SetSize(36);

	//scene->Add(text);


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

	CreateZako(scene, glm::vec3{ 0,0,1 }, 32);

	StreamEngine::SceneManager::GetInstance().SetActiveScene("Demo");
}
