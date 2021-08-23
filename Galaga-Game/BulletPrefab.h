#pragma once
#include <memory>

#include "BasicEnemyBehavior.h"
#include "BulletBehavior.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "Controller.h"
#include "Scene.h"
#include "GameObject.h"
#include "PlayerBehavior.h"
#include "SpriteTextureComponent.h"

inline std::shared_ptr<Controller> CreateBullet(const std::shared_ptr<StreamEngine::Scene>& pScene, const glm::vec3& startingPos, float size, Shooter shooter)
{
	std::shared_ptr<StreamEngine::GameObject> bulletObject{ std::make_shared<StreamEngine::GameObject>("bullet")};
	std::shared_ptr<Controller> bulletController{ std::make_shared<Controller>(bulletObject) };
	bulletObject->AddComponent(bulletController);
	const std::shared_ptr<SpriteTextureComponent> spriteComponent{ std::make_shared<SpriteTextureComponent>("Arcade - Galaga - General Sprites.png", bulletObject) };
	spriteComponent->AddSrcRect(Rect{ 136,307,16,16 });
	spriteComponent->SetSrcRectIdx(0);
	bulletObject->AddComponent(spriteComponent);
	bulletObject->GetTransform().SetPosition(startingPos);
	bulletObject->GetTransform().SetHeight(size);
	bulletObject->GetTransform().SetWidth(size);

	const std::shared_ptr<BulletBehavior> bulletBehavior{ std::make_shared<BulletBehavior>(bulletObject, shooter) };
	bulletObject->AddComponent(bulletBehavior);

	const std::shared_ptr<StreamEngine::CollisionComponent> collisionComponent{ std::make_shared<StreamEngine::CollisionComponent>(bulletObject) };
	collisionComponent->SetOverlapFunction([bulletBehavior](const std::shared_ptr<StreamEngine::GameObject>& other)
		{
			if (other->GetName() != "bullet")
			{
				const std::shared_ptr<BasicEnemyBehavior> enemyBehavior = other->GetComponent<BasicEnemyBehavior>();
				if (enemyBehavior != nullptr)
				{
					enemyBehavior->Die();
				}
				else
				{
					const std::shared_ptr<PlayerBehavior> playerBehavior = other->GetComponent<PlayerBehavior>();
					if (playerBehavior != nullptr)
					{
						playerBehavior->Die();
					}
				}
				bulletBehavior->Die();
			}
		});

	bulletObject->AddComponent(collisionComponent);
	StreamEngine::CollisionManager::GetInstance().AddCollisionComponent(collisionComponent);

	pScene->Add(bulletObject);
	return bulletController;
}
