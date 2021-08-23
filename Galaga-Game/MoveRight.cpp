#include "stdafx.h"
#include "MoveRight.h"

#include <utility>

#include "PlayerBehavior.h"
#include "GameObject.h"

MoveRight::MoveRight(std::weak_ptr<PlayerBehavior> pActingObjectController)
	:m_pActingObjectController(std::move(pActingObjectController))
{
}

void MoveRight::Execute()
{
	m_pActingObjectController.lock()->MoveRight();
}
