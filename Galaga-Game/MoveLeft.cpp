#include "stdafx.h"
#include "MoveLeft.h"

#include <utility>

#include "PlayerBehavior.h"
#include "GameObject.h"

MoveLeft::MoveLeft(std::weak_ptr<PlayerBehavior> pActingObjectController)
	:m_pActingObjectController(std::move(pActingObjectController))
{
}

void MoveLeft::Execute()
{
	m_pActingObjectController.lock()->MoveLeft();
}
