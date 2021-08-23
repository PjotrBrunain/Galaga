#pragma once
#include <memory>

#include "Controller.h"
#include "Scene.h"
#include "GameObject.h"
#include "SpriteTextureComponent.h"
#include "BasicEnemyBehavior.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameInstance.h"
#include "PlayerBehavior.h"
#include "ScoreObserver.h"
#include "SubjectComponent.h"

inline std::shared_ptr<Controller> CreateGoei(const std::shared_ptr<StreamEngine::Scene>& pScene, const glm::vec3& startingPos, float size, float startDelay)
{
	//Enemy
	std::shared_ptr<StreamEngine::GameObject> enemyObject{ std::make_shared<StreamEngine::GameObject>() };
	const std::shared_ptr<Controller> enemyController{ std::make_shared<Controller>(enemyObject) };
	enemyObject->AddComponent(enemyController);
	const std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - Galaga - General Sprites.png", enemyObject) };
	spriteComponent->AddSrcRect(Rect{ 73, 109, 16, 16 });
	spriteComponent->AddSrcRect(Rect{ 73,91,16,16 });
	spriteComponent->AddSrcRect(Rect{ 73,73,16,16 });
	spriteComponent->AddSrcRect(Rect{ 73,55,16,16 });
	spriteComponent->AddSrcRect(Rect{ 73,37,16,16 });
	spriteComponent->AddSrcRect(Rect{ 73,19,16,16 });
	spriteComponent->AddSrcRect(Rect{ 73,1,16,16 });
	spriteComponent->SetSrcRectIdx(0);
	enemyObject->AddComponent(spriteComponent);

	enemyObject->GetTransform().SetPosition(0, 0, 0);
	enemyObject->GetTransform().SetWidth(size);
	enemyObject->GetTransform().SetHeight(size);

	const auto& gameInstance{ GameInstance::GetInstance() };
	std::vector<Point> startingBeziers{ Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), gameInstance.GetScreenMinY() },
				Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.3f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() },
				Point{ gameInstance.GetScreenMinX(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() },
				Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() },
				Point{int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
				Point{gameInstance.GetScreenMinX() + gameInstance.GetScreenWidth(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
				Point{int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.3f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
				Point{int(startingPos.x), int(startingPos.y)} };

	const std::shared_ptr<BasicEnemyBehavior> goeiBehavior{ std::make_shared<BasicEnemyBehavior>(enemyObject, enemyController, startingBeziers, EnemyType::Goei, startDelay) };
	enemyObject->AddComponent(goeiBehavior);
	const std::shared_ptr<SubjectComponent> subject{ std::make_shared<SubjectComponent>(enemyObject) };

	const std::shared_ptr<ScoreObserver> scoreObserver{ std::make_shared<ScoreObserver>() };

	subject->AddObserver(scoreObserver);

	enemyObject->AddComponent(subject);

	const std::shared_ptr<StreamEngine::CollisionComponent> collisionComponent{ std::make_shared<StreamEngine::CollisionComponent>(enemyObject) };
	collisionComponent->SetOverlapFunction([goeiBehavior](const std::shared_ptr<StreamEngine::GameObject>& other)
		{
			if (other->GetName() == "Player")
			{
				goeiBehavior->Die();
				std::shared_ptr<PlayerBehavior> playerBehavior = other->GetComponent<PlayerBehavior>();
				if (playerBehavior != nullptr)
				{
					playerBehavior->Die();
				}
			}
			else if (other->GetName() == "bullet")
			{
				goeiBehavior->Die();
			}
		});

	enemyObject->AddComponent(collisionComponent);

	StreamEngine::CollisionManager::GetInstance().AddCollisionComponent(collisionComponent);

	pScene->Add(enemyObject);
	return enemyController;
}
