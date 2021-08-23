#include "stdafx.h"
#include "Shoot.h"

#include "PlayerBehavior.h"
#include "Enums.h"

Shoot::Shoot(std::weak_ptr<PlayerBehavior> pActingBehavior)
	:m_pActingBehavior(std::move(pActingBehavior))
{
}

void Shoot::Execute()
{
	m_pActingBehavior.lock()->Shoot(Shooter::Player);
}
