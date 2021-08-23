#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

namespace StreamEngine
{
	class CollisionComponent;

	class CollisionManager final : public StreamEngine::Singleton<CollisionManager>
	{
	public:
		void CheckCollisions(const std::shared_ptr<CollisionComponent>& currentComponent);

		void AddCollisionComponent(const std::weak_ptr<CollisionComponent>& pComponent);

	private:
		std::vector<std::weak_ptr<CollisionComponent>> m_pCollisionComponents{};

		static bool IsOverlapping(const std::shared_ptr<CollisionComponent>& pCurrentComponent, const std::shared_ptr<CollisionComponent>& pCheckComponent);
	};
}
