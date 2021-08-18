#include "Controller.h"

#include <utility>
#include "GameObject.h"

#include "GameInstance.h"

Controller::Controller(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_MoveSpeed(8.f)
{
}

void Controller::MoveRight() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.x += m_MoveSpeed;
	currentPos.x = std::min(currentPos.x, float(GameInstance::GetInstance().GetScreenMinX() + GameInstance::GetInstance().GetScreenWidth()) - m_pOwningGameObject.lock()->GetTransform().GetWidth());
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveLeft() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.x -= m_MoveSpeed;
	currentPos.x = std::max(currentPos.x, float(GameInstance::GetInstance().GetScreenMinX()));
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveUp() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.y -= m_MoveSpeed;
	currentPos.y = std::max(currentPos.y, float(GameInstance::GetInstance().GetScreenMinY()));
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveDown() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.y += m_MoveSpeed;
	currentPos.y = std::min(currentPos.y, float(GameInstance::GetInstance().GetScreenHeight() + GameInstance::GetInstance().GetScreenMinY()) - m_pOwningGameObject.lock()->GetTransform().GetHeight());
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}
