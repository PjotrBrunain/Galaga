#include "MiniginPCH.h"
#include "BaseComponent.h"

StreamEngine::BaseComponent::BaseComponent(const bool isVisual, std::weak_ptr<GameObject> pOwningGameObject)
	:m_IsVisual(isVisual),
	m_pOwningGameObject(pOwningGameObject)
{
}

bool StreamEngine::BaseComponent::IsVisual() const
{
	return m_IsVisual;
}
