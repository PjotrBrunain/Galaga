#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

namespace StreamEngine
{
	class Observer;

	class ObserverManager final : public Singleton<ObserverManager>
	{
	public:
		~ObserverManager() = default;
		void AddObserver(const std::shared_ptr<Observer>& observer);

	private:
		std::vector<std::shared_ptr<Observer>> m_Observers{};
	};
}
