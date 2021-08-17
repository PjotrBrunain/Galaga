#include "Shoot.h"

Shoot::Shoot(std::shared_ptr<StreamEngine::GameObject> pActingObject)
	:m_pActingObject(std::move(pActingObject))
{
}

void Shoot::Execute()
{

}
