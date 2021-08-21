#include "PlayerBehavior.h"

PlayerBehavior::PlayerBehavior(const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject)
	:BaseComponent(false, pOwningGameObject),
	m_HasDied()
{
}

void PlayerBehavior::Die()
{
	if (!m_HasDied)
	{
		m_HasDied = true;
	}
}
