#include "MiniginPCH.h"
#include "GameObject.h"
#include "algorithm"

StreamEngine::Transform& StreamEngine::GameObject::GetTransform()
{
	return m_Transform;
}

void StreamEngine::GameObject::Render()
{
	if (m_IsVisual && m_IsActive)
	{
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [](std::shared_ptr<BaseComponent> pComponent) {if (pComponent != nullptr && pComponent->IsVisual()) pComponent->Render(); });
	}
}

bool StreamEngine::GameObject::IsVisual() const
{
	return m_IsVisual;
}

void StreamEngine::GameObject::AddChild(const std::shared_ptr<GameObject>& pChild)
{
	m_pChildObjects.push_back(pChild);
}

std::string StreamEngine::GameObject::GetName() const
{
	return m_Name;
}

void StreamEngine::GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

void StreamEngine::GameObject::SetOwner(const std::weak_ptr<GameObject> owner)
{
	m_pOwner = owner;
}

void StreamEngine::GameObject::SetIsVisual(bool isVisual)
{
	m_IsVisual = isVisual;
}

void StreamEngine::GameObject::SetIsActive(bool isActive)
{
	m_IsActive = isActive;
}

bool StreamEngine::GameObject::GetIsActive() const
{
	return m_IsActive;
}

void StreamEngine::GameObject::SetToRemove(bool toRemove)
{
	m_ToRemove = toRemove;
}

bool StreamEngine::GameObject::GetToRemove() const
{
	return m_ToRemove;
}

StreamEngine::GameObject::GameObject(std::string name)
	:m_Name(name)
{
}

StreamEngine::GameObject::~GameObject() = default;

void StreamEngine::GameObject::Update(float deltaTime)
{
	if (m_IsActive)
	{
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) { if (pComponent != nullptr) pComponent->Update(deltaTime); });
	}
}

void StreamEngine::GameObject::FixedUpdate(float deltaTime)
{
	if (m_IsActive)
	{
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) {if (pComponent != nullptr) pComponent->FixedUpdate(deltaTime); });
	}
}

void StreamEngine::GameObject::LateUpdate(float deltaTime)
{
	if (m_IsActive)
	{
		std::for_each(m_pComponents.begin(), m_pComponents.end(), [deltaTime](std::shared_ptr<BaseComponent> pComponent) {if (pComponent != nullptr) pComponent->LateUpdate(deltaTime); });
	}
}

void StreamEngine::GameObject::AddComponent(const std::shared_ptr<BaseComponent> pComponent)
{
	m_pComponents.push_back(pComponent);
	m_IsVisual = m_IsVisual || pComponent->IsVisual();
}
