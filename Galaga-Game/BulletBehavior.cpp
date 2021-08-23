#include "stdafx.h"
#include "BulletBehavior.h"
#include "GameObject.h"

#include <utility>

BulletBehavior::BulletBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject, Shooter shooter)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_Speed(4.f),
	m_Shooter(shooter)
{
}

#pragma warning (push)
#pragma warning (disable:4100)
void BulletBehavior::Update(float deltaTime)
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	switch (m_Shooter)
	{
	case Shooter::Player:
		currentPos.y -= m_Speed;
		break;
	case Shooter::Enemy:
		currentPos.y += m_Speed;
		break;
	}

	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}
#pragma warning (pop)

void BulletBehavior::Die() const
{
	m_pOwningGameObject.lock()->SetIsActive(false);
	m_pOwningGameObject.lock()->SetToRemove(true);
}
