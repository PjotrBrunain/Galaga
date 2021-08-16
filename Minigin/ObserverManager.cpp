#include "MiniginPCH.h"
#include "ObserverManager.h"

void StreamEngine::ObserverManager::AddObserver(const std::shared_ptr<Observer>& observer)
{
	m_Observers.push_back(observer);
}
