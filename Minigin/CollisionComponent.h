#pragma once
#include <functional>

#include "BaseComponent.h"

namespace StreamEngine
{
	class CollisionComponent final : public BaseComponent, public std::enable_shared_from_this<CollisionComponent>
	{
	public:
		CollisionComponent(std::weak_ptr<GameObject> pOwningGameObject);
		virtual ~CollisionComponent() = default;

		void FixedUpdate(float deltaTime) override;

		void RunOverlapFunction(const std::shared_ptr<GameObject>& object) const;
		void SetOverlapFunction(const std::function<void(std::shared_ptr<GameObject>)>& overlapFunction);

		CollisionComponent(const CollisionComponent&) = delete;
		CollisionComponent(CollisionComponent&&) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent&) = delete;
		CollisionComponent& operator=(CollisionComponent&&) noexcept = delete;
	private:
		std::function<void(std::shared_ptr<GameObject>)> m_OverlapFunction;
	};
}
