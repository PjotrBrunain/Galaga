#pragma once
#include <memory>
#include <SDL_keycode.h>

#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "Controller.h"
#include "PlayerBehavior.h"
#include "Scene.h"
#include "SpriteTextureComponent.h"
#include "BasicEnemyBehavior.h"
#include "Shoot.h"

inline std::shared_ptr<StreamEngine::GameObject> CreatePlayer(const std::shared_ptr<StreamEngine::Scene>& pScene, int playerNumber, const glm::vec3& startingPos, float size)
{
	//Player
	std::shared_ptr<StreamEngine::GameObject> playerObject{ std::make_shared<StreamEngine::GameObject>() };
	std::shared_ptr<Controller> playerController{ std::make_shared<Controller>(playerObject) };
	playerObject->AddComponent(playerController);
	const std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - Galaga - General Sprites.png", playerObject) };

	if (playerNumber == 0)
		spriteComponent->AddSrcRect(Rect{ 1,109,16,16 });
	else if (playerNumber == 1)
	{
		spriteComponent->AddSrcRect(Rect{ 19,109,16,16 });
	}

	spriteComponent->SetSrcRectIdx(0);
	playerObject->AddComponent(spriteComponent);

	playerObject->GetTransform().SetPosition(startingPos);
	playerObject->GetTransform().SetWidth(size);
	playerObject->GetTransform().SetHeight(size);

	pScene->Add(playerObject);

	const std::shared_ptr<PlayerBehavior> playerBehavior{ std::make_shared<PlayerBehavior>(playerObject,Player(playerNumber), playerController) };
	playerObject->AddComponent(playerBehavior);

	//PlayerCommands
	const std::shared_ptr<MoveRight> pMoveRightCommand{ std::make_shared<MoveRight>(playerBehavior) };
	const std::shared_ptr<MoveLeft> pMoveLeftCommand{ std::make_shared<MoveLeft>(playerBehavior) };
	const std::shared_ptr<Shoot> pShootCommand{ std::make_shared<Shoot>(playerBehavior) };
	if (playerNumber == 0)
	{
		const StreamEngine::FlexibleCommand flexiMoveRight{ pMoveRightCommand, false, XINPUT_GAMEPAD_DPAD_RIGHT, 0, SDLK_d };
		pScene->AddCommand(flexiMoveRight);
		const StreamEngine::FlexibleCommand flexiMoveLeft{ pMoveLeftCommand, false, XINPUT_GAMEPAD_DPAD_LEFT, 0, SDLK_a };
		pScene->AddCommand(flexiMoveLeft);
		const StreamEngine::FlexibleCommand flexiShoot{ pShootCommand, true, XINPUT_GAMEPAD_A, 0, SDLK_SPACE };
		pScene->AddCommand(flexiShoot);
	}
	else if (playerNumber == 1)
	{
		const StreamEngine::FlexibleCommand flexiMoveRight{ pMoveRightCommand, false, XINPUT_GAMEPAD_DPAD_RIGHT, 1, SDLK_RIGHT };
		pScene->AddCommand(flexiMoveRight);
		const StreamEngine::FlexibleCommand flexiMoveLeft{ pMoveLeftCommand, false, XINPUT_GAMEPAD_DPAD_LEFT, 1, SDLK_LEFT };
		pScene->AddCommand(flexiMoveLeft);
		const StreamEngine::FlexibleCommand flexiShoot{ pShootCommand, true, XINPUT_GAMEPAD_A, 1, SDLK_UP };
		pScene->AddCommand(flexiShoot);
	}



	const std::shared_ptr<StreamEngine::CollisionComponent> collisionComponent{ std::make_shared<StreamEngine::CollisionComponent>(playerObject) };
	collisionComponent->SetOverlapFunction([playerBehavior](std::shared_ptr<StreamEngine::GameObject> other)
		{
			if (other->GetName() != "Player" && other->GetName() != "bullet")
			{
				playerBehavior->Die();
				const std::shared_ptr<BasicEnemyBehavior> enemyBehavior = other->GetComponent<BasicEnemyBehavior>();
				if (enemyBehavior != nullptr)
				{
					enemyBehavior->Die();
				}
			}
		});

	playerObject->AddComponent(collisionComponent);

	StreamEngine::CollisionManager::GetInstance().AddCollisionComponent(collisionComponent);

	return playerObject;
}
