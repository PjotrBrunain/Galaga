#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "GameObject.h"

#include "ResourceManager.h"
#include "Renderer.h"

StreamEngine::TextureComponent::TextureComponent(const std::string& texturePath, std::weak_ptr<GameObject> pOwningGameObject)
	:BaseComponent(true, pOwningGameObject),
	m_pTexture()
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void StreamEngine::TextureComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_pTexture.lock().get(), m_pOwningGameObject.lock()->GetTransform().GetPosition().x, m_pOwningGameObject.lock()->GetTransform().GetPosition().y);
}
