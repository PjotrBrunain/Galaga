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
#include "GameOverBehavior.h"
#include "GoeiPrefab.h"
#include "PlayerPrefab.h"
#include "Scene.h"
#include "SelectCommand.h"
#include "SelectComponent.h"
#include "SelectDownCommand.h"
#include "SelectUpCommand.h"
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

	CreateZako(scene, glm::vec3{ 0.4f * GameInstance::GetInstance().GetScreenWidth() + GameInstance::GetInstance().GetScreenMinX(),0.2f* GameInstance::GetInstance().GetScreenHeight() + GameInstance::GetInstance().GetScreenMinY(),1 }, 48, 0);

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
							float startDelay{};
							do
							{
								if (line.find("\"x\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									x = std::stof(line);
								}
								else if (line.find("\"y\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									y = std::stof(line);
								}
								else if (line.find("\"size\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									size = std::stof(line);
								}
								else if (line.find("\"StartDelay\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									startDelay = std::stof(line);
								}
								std::getline(fileStream, line);
								ss = std::stringstream{ line };
							} while (line.find("}") == std::string::npos);
							CreateZako(scene, glm::vec3{ x * float(GameInstance::GetInstance().GetScreenWidth()) + GameInstance::GetInstance().GetScreenMinX(),y * float(GameInstance::GetInstance().GetScreenHeight()) + GameInstance::GetInstance().GetScreenMinY(),1 }, size, startDelay * 200);
						}
					} while (line.find("]") == std::string::npos);
				}
				if (line.find("goeis") != std::string::npos)
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
							float startDelay{};
							do
							{
								if (line.find("\"x\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									x = std::stof(line);
								}
								else if (line.find("\"y\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									y = std::stof(line);
								}
								else if (line.find("\"size\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									size = std::stof(line);
								}
								else if (line.find("\"StartDelay\"") != std::string::npos)
								{
									std::getline(ss, line, ':');
									std::getline(ss, line);
									startDelay = std::stof(line);
								}
								std::getline(fileStream, line);
								ss = std::stringstream{ line };
							} while (line.find("}") == std::string::npos);
							CreateGoei(scene, glm::vec3{ x,y,1 }, size, startDelay * 1000);
						}
					} while (line.find("]") == std::string::npos);
				}
			}
		} while (!fileStream.eof());
	}
}

inline void LoadLevel(const std::string& filePath, const std::shared_ptr<StreamEngine::GameObject>& fpsCounter, const std::string& levelName)
{
	const auto& sceneLevel1 = StreamEngine::SceneManager::GetInstance().CreateScene(levelName);

	ReadLevelFromFile(filePath, sceneLevel1);

	sceneLevel1->Add(fpsCounter);

	std::shared_ptr<StreamEngine::GameObject> points{ std::make_shared<StreamEngine::GameObject>("pointsText") };
	std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",points) };
	textComp->SetSize(32);
	textComp->SetColor(SDL_Color{ 255, 255, 255,255 });
	textComp->SetText("0");
	points->AddComponent(textComp);
	sceneLevel1->Add(points);

	points->GetTransform().SetPosition(glm::vec3{ 760, 20,1 });
}

inline void LoadGalagaFunction()
{
	// global fps counter
	std::shared_ptr<StreamEngine::GameObject> fpsCounter{ std::make_shared<StreamEngine::GameObject>("fpsComponent")};
	{
		const std::shared_ptr<StreamEngine::TextComponent> pTxtComponent{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf",fpsCounter) };
		pTxtComponent->SetSize(26);
		pTxtComponent->SetColor({ 0,255,0,255 });
		const std::shared_ptr<StreamEngine::FPSComponent> pFPSComponent{ std::make_shared<StreamEngine::FPSComponent>(fpsCounter) };
		pTxtComponent->LinkText(pFPSComponent->GetTextLink());
		pTxtComponent->SetDoUpdate(true);

		fpsCounter->AddComponent(pTxtComponent);
		fpsCounter->AddComponent(pFPSComponent);

		fpsCounter->GetTransform().SetPosition(0, 0, 0);
	}

	//StartScreen
	{
		const auto& sceneStartScreen = StreamEngine::SceneManager::GetInstance().CreateScene("StartScreen");

		std::shared_ptr<StreamEngine::GameObject> logo{ std::make_shared<StreamEngine::GameObject>("logo") };
		std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf", logo) };
		textComp->SetColor(SDL_Color{ 255,255,255,255 });
		textComp->SetSize(48);
		textComp->SetText("Galaga");
		logo->AddComponent(textComp);

		logo->GetTransform().SetPosition(20, 20, 1);
		sceneStartScreen->Add(logo);

		std::shared_ptr<StreamEngine::GameObject> SingleplayerText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", SingleplayerText);
		textComp->SetColor(SDL_Color{ 255, 255, 255, 255 });
		textComp->SetSize(32);
		textComp->SetText("SinglePlayer");
		SingleplayerText->AddComponent(textComp);

		SingleplayerText->GetTransform().SetPosition(64, 100, 1);
		sceneStartScreen->Add(SingleplayerText);

		std::shared_ptr<StreamEngine::GameObject> CoopText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", CoopText);
		textComp->SetColor(SDL_Color{ 255, 255, 255, 255 });
		textComp->SetSize(32);
		textComp->SetText("Co op");
		CoopText->AddComponent(textComp);

		CoopText->GetTransform().SetPosition(64, 180, 1);
		sceneStartScreen->Add(CoopText);

		std::shared_ptr<StreamEngine::GameObject> VersusText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", VersusText);
		textComp->SetColor(SDL_Color{ 255, 255, 255, 255 });
		textComp->SetSize(32);
		textComp->SetText("Versus");
		VersusText->AddComponent(textComp);

		VersusText->GetTransform().SetPosition(64, 260, 1);
		sceneStartScreen->Add(VersusText);

		std::shared_ptr < StreamEngine::GameObject> selector{ std::make_shared<StreamEngine::GameObject>() };
		std::shared_ptr<SpriteTextureComponent> spriteTextureComponent{ std::make_shared<SpriteTextureComponent>("Arcade - Galaga - General Sprites.png", selector) };
		spriteTextureComponent->AddSrcRect(Rect{ 136,289,16,16 });
		spriteTextureComponent->SetSrcRectIdx(0);

		selector->AddComponent(spriteTextureComponent);
		selector->GetTransform().SetHeight(32);
		selector->GetTransform().SetWidth(32);
		selector->GetTransform().SetPosition(16, 100, 1);
		sceneStartScreen->Add(selector);

		std::shared_ptr<SelectComponent> selectComponent{ std::make_shared<SelectComponent>(selector) };
		selectComponent->AddSelectedPos({ 16,100,1 });
		selectComponent->AddSelectedPos({ 16,180,1 });
		selectComponent->AddSelectedPos({ 16,260,1 });
		selectComponent->SetSelected(0);
		selector->AddComponent(selectComponent);

		sceneStartScreen->AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectDownCommand>(selector), true, XINPUT_GAMEPAD_DPAD_DOWN, 0, SDLK_s, 0 });
		sceneStartScreen->AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectUpCommand>(selector), true, XINPUT_GAMEPAD_DPAD_UP, 0, SDLK_w,0 });
		sceneStartScreen->AddCommand(StreamEngine::FlexibleCommand{ std::make_shared<SelectCommand>(selector), true, XINPUT_GAMEPAD_A, 0, SDLK_RETURN, 0 });
		sceneStartScreen->Add(fpsCounter);
	}

	//Levels
	{
		LoadLevel("../Data/Level1.json", fpsCounter, "Level1");
		LoadLevel("../Data/Level2.json", fpsCounter, "Level2");
		LoadLevel("../Data/Level3.json", fpsCounter, "Level3");

	}

	//GameOverScreen
	{
		const auto& sceneGameOverScreen{ StreamEngine::SceneManager::GetInstance().CreateScene("GameOverScreen") };

		std::shared_ptr<StreamEngine::GameObject> resultsText{ std::make_shared<StreamEngine::GameObject>() };
		std::shared_ptr<StreamEngine::TextComponent> textComp{ std::make_shared<StreamEngine::TextComponent>("Lingua.otf", resultsText) };
		textComp->SetColor(SDL_Color{ 176,0,0,255 });
		textComp->SetSize(32);
		textComp->SetText("--RESULTS--");
		resultsText->AddComponent(textComp);

		resultsText->GetTransform().SetPosition(20, 20, 1);
		sceneGameOverScreen->Add(resultsText);

		std::shared_ptr<StreamEngine::GameObject> shotsFiredText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", shotsFiredText);
		textComp->SetColor(SDL_Color{ 252,207,3,255 });
		textComp->SetSize(32);
		textComp->SetText("SHOTS FIRED:");
		shotsFiredText->AddComponent(textComp);

		shotsFiredText->GetTransform().SetPosition(20, 60, 1);
		sceneGameOverScreen->Add(shotsFiredText);

		std::shared_ptr<StreamEngine::GameObject> numberOfHitsText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", numberOfHitsText);
		textComp->SetColor(SDL_Color{ 252,207,3,255 });
		textComp->SetSize(32);
		textComp->SetText("NUMBER OF HITS:");
		numberOfHitsText->AddComponent(textComp);

		numberOfHitsText->GetTransform().SetPosition(20, 100, 1);
		sceneGameOverScreen->Add(numberOfHitsText);

		std::shared_ptr<StreamEngine::GameObject> hitMissRatioText{ std::make_shared<StreamEngine::GameObject>() };
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", hitMissRatioText);
		textComp->SetColor(SDL_Color{ 255,255,255,255 });
		textComp->SetSize(32);
		textComp->SetText("HIT MISSRATIO:");
		hitMissRatioText->AddComponent(textComp);

		hitMissRatioText->GetTransform().SetPosition(20, 140, 1);
		sceneGameOverScreen->Add(hitMissRatioText);

		std::shared_ptr<StreamEngine::GameObject> shotsFiredLink{ std::make_shared<StreamEngine::GameObject>("shotsFired")};
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", shotsFiredLink);
		textComp->SetColor(SDL_Color{ 252,207,3,255 });
		textComp->SetSize(32);
		textComp->SetText("32");
		shotsFiredLink->AddComponent(textComp);

		shotsFiredLink->GetTransform().SetPosition(320, 60, 1);
		sceneGameOverScreen->Add(shotsFiredLink);

		std::shared_ptr<StreamEngine::GameObject> numberOfHitsLink{ std::make_shared<StreamEngine::GameObject>("NumberOfHits")};
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", numberOfHitsLink);
		textComp->SetColor(SDL_Color{ 252,207,3,255 });
		textComp->SetSize(32);
		textComp->SetText("32");
		numberOfHitsLink->AddComponent(textComp);

		numberOfHitsLink->GetTransform().SetPosition(320, 100, 1);
		sceneGameOverScreen->Add(numberOfHitsLink);

		std::shared_ptr<StreamEngine::GameObject> hitMissLink{ std::make_shared<StreamEngine::GameObject>("hitMissPercentage")};
		textComp = std::make_shared<StreamEngine::TextComponent>("Lingua.otf", hitMissLink);
		textComp->SetColor(SDL_Color{ 255,255,255,255 });
		textComp->SetSize(32);
		textComp->SetText("%32");
		hitMissLink->AddComponent(textComp);

		hitMissLink->GetTransform().SetPosition(320, 140, 1);
		sceneGameOverScreen->Add(hitMissLink);

		sceneGameOverScreen->Add(fpsCounter);

		std::shared_ptr<StreamEngine::GameObject> gameOverBehaviorObject{ std::make_shared<StreamEngine::GameObject>("gameOverBehavior")};
		const std::shared_ptr<GameOverBehavior> gameOverBehavior{ std::make_shared<GameOverBehavior>(gameOverBehaviorObject) };
		gameOverBehaviorObject->AddComponent(gameOverBehavior);

		sceneGameOverScreen->Add(gameOverBehaviorObject);
	}

	StreamEngine::SceneManager::GetInstance().SetActiveScene("StartScreen");
}
