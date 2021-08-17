#include "MoveRight.h"

#include <utility>

#include "Controller.h"
#include "GameObject.h"

MoveRight::MoveRight(std::shared_ptr<Controller> pActingObjectController)
	:m_pActingObjectController(std::move(pActingObjectController))
{
}

void MoveRight::Execute()
{
	m_pActingObjectController->MoveRight();
}
