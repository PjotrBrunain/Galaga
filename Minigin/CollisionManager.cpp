#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "GameObject.h"

void StreamEngine::CollisionManager::CheckCollisions(const std::shared_ptr<CollisionComponent>& currentComponent)
{
	for (const std::shared_ptr<CollisionComponent>& pCollisionComponent : m_pCollisionComponents)
	{
		if (pCollisionComponent != currentComponent)
		{
			if (IsOverlapping(currentComponent, pCollisionComponent))
			{
				pCollisionComponent->RunOverlapFunction(currentComponent->GetOwner());
				currentComponent->RunOverlapFunction(pCollisionComponent->GetOwner());
			}
		}
	}
}

void StreamEngine::CollisionManager::AddCollisionComponent(const std::shared_ptr<CollisionComponent>& pComponent)
{
	m_pCollisionComponents.push_back(pComponent);
}

bool StreamEngine::CollisionManager::IsOverlapping(const std::shared_ptr<CollisionComponent>& pCurrentComponent,
	const std::shared_ptr<CollisionComponent>& pCheckComponent)
{
	const glm::vec3 currentPos{ pCurrentComponent->GetOwner()->GetTransform().GetPosition() };
	const float currentWidth{ pCurrentComponent->GetOwner()->GetTransform().GetWidth() };
	const float currentHeight{ pCurrentComponent->GetOwner()->GetTransform().GetHeight() };
	const glm::vec3 checkPos{ pCheckComponent->GetOwner()->GetTransform().GetPosition() };
	const float checkWidth{ pCheckComponent->GetOwner()->GetTransform().GetWidth() };
	const float checkHeight{ pCheckComponent->GetOwner()->GetTransform().GetHeight() };

	if (currentPos.x >= checkPos.x && currentPos.x <= checkPos.x + checkWidth &&
		currentPos.y >= checkPos.y && currentPos.y <= checkPos.y + checkHeight)
		return true;

	if (currentPos.x + currentWidth >= checkPos.x && currentPos.x + currentWidth <= checkPos.x + checkWidth &&
		currentPos.y >= checkPos.y && currentPos.y <= checkPos.y + checkHeight)
		return true;

	if (currentPos.x >= checkPos.x && currentPos.x <= checkPos.x + checkWidth &&
		currentPos.y + currentWidth >= checkPos.y && currentPos.y + currentHeight <= checkPos.y + checkHeight)
		return true;

	if (currentPos.x + currentWidth >= checkPos.x && currentPos.x + currentWidth <= checkPos.x + checkWidth &&
		currentPos.y + currentWidth >= checkPos.y && currentPos.y + currentHeight <= checkPos.y + checkHeight)
		return true;

	return false;
}
