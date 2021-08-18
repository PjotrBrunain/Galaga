#pragma once
#include <memory>

namespace StreamEngine
{
	class GameObject;

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void OnNotify(const std::shared_ptr<GameObject>& pEntity, int event) = 0;

		Observer(const Observer&) = delete;
		Observer(Observer&&) noexcept = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(Observer&&) noexcept = delete;
	};
}
