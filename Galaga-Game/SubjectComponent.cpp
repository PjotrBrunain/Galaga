#include "stdafx.h"
#include "SubjectComponent.h"
#include "Observer.h"

SubjectComponent::SubjectComponent(const std::weak_ptr<StreamEngine::GameObject>& pOwningObject)
	:BaseComponent(false, pOwningObject)
{
}

void SubjectComponent::AddObserver(const std::shared_ptr<StreamEngine::Observer>& pObserver)
{
	m_pObservers.push_back(pObserver);
}

void SubjectComponent::RemoveObserver(const std::shared_ptr<StreamEngine::Observer>& pObserver)
{
	auto it{ std::find(m_pObservers.begin(), m_pObservers.end(), pObserver) };
	if (it == m_pObservers.end())
	{
		return;
	}
	m_pObservers.erase(it);
}

void SubjectComponent::Notify(const std::shared_ptr<StreamEngine::GameObject>& pEntity, int event)
{
	for (const std::shared_ptr<StreamEngine::Observer>& pObserver : m_pObservers)
	{
		pObserver->OnNotify(pEntity, event);
	}
}
