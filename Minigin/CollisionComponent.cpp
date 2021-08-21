#include "MiniginPCH.h"
#include "CollisionComponent.h"

#include "CollisionManager.h"

StreamEngine::CollisionComponent::CollisionComponent(std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(false, pOwningGameObject)
{
}
#pragma warning (push)
#pragma warning (disable:4100)
void StreamEngine::CollisionComponent::FixedUpdate(float deltaTime)
{
	CollisionManager::GetInstance().CheckCollisions(shared_from_this());
}
#pragma warning (pop)
void StreamEngine::CollisionComponent::RunOverlapFunction(const std::shared_ptr<GameObject>& object) const
{
	m_OverlapFunction(object);
}

void StreamEngine::CollisionComponent::SetOverlapFunction(const std::function<void(std::shared_ptr<GameObject>)>& overlapFunction)
{
	m_OverlapFunction = overlapFunction;
}
