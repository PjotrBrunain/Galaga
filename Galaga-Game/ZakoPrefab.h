#pragma once
#include <memory>

#include "Controller.h"
#include "Scene.h"
#include "GameObject.h"
#include "SpriteTextureComponent.h"
#include "ZakoBehavior.h"

inline std::shared_ptr<Controller> CreateZako(const std::shared_ptr<StreamEngine::Scene>& pScene, const glm::vec3& startingPos, float size)
{
	//Enemy
	std::shared_ptr<StreamEngine::GameObject> enemyObject{ std::make_shared<StreamEngine::GameObject>() };
	const std::shared_ptr<Controller> enemyController{ std::make_shared<Controller>(enemyObject) };
	enemyObject->AddComponent(enemyController);
	const std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - Galaga - General Sprites.png", enemyObject) };
	spriteComponent->AddSrcRect(Rect{ 91,109,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,91,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,73,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,55,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,37,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,19,16,16 });
	spriteComponent->AddSrcRect(Rect{ 91,1,16,16 });
	spriteComponent->SetSrcRectIdx(0);
	enemyObject->AddComponent(spriteComponent);

	enemyObject->GetTransform().SetPosition(startingPos);
	enemyObject->GetTransform().SetWidth(size);
	enemyObject->GetTransform().SetHeight(size);

	const std::shared_ptr<ZakoBehavior> zakoBehavior{ std::make_shared<ZakoBehavior>(enemyObject, enemyController) };
	enemyObject->AddComponent(zakoBehavior);

	pScene->Add(enemyObject);

	return enemyController;
}
