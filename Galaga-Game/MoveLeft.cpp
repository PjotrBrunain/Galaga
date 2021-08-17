#include "MoveLeft.h"

#include <utility>

#include "Controller.h"
#include "GameObject.h"

MoveLeft::MoveLeft(std::shared_ptr<Controller> pActingObjectController)
	:m_pActingObjectController(std::move(pActingObjectController))
{
}

void MoveLeft::Execute()
{
	m_pActingObjectController->MoveLeft();
}
