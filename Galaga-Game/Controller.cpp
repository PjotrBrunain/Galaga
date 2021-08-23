#include "stdafx.h"
#include "Controller.h"

#include <algorithm>

#include "BulletPrefab.h"
#include "GameObject.h"

#include "GameInstance.h"
#include "SceneManager.h"

Controller::Controller(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_MoveSpeed(16.f)
{
}

void Controller::MoveRight() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.x += m_MoveSpeed;
	currentPos.x = currentPos.x < float(GameInstance::GetInstance().GetScreenMinX() + GameInstance::GetInstance().GetScreenWidth()) - m_pOwningGameObject.lock()->GetTransform().GetWidth() ? currentPos.x : float(GameInstance::GetInstance().GetScreenMinX() + GameInstance::GetInstance().GetScreenWidth()) - m_pOwningGameObject.lock()->GetTransform().GetWidth();
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveLeft() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.x -= m_MoveSpeed;
	currentPos.x = currentPos.x > float(GameInstance::GetInstance().GetScreenMinX()) ? currentPos.x : float(GameInstance::GetInstance().GetScreenMinX());
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveUp() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.y -= m_MoveSpeed;
	currentPos.y = currentPos.y > float(GameInstance::GetInstance().GetScreenMinY()) ? currentPos.y : float(GameInstance::GetInstance().GetScreenMinY());
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::MoveDown() const
{
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.y += m_MoveSpeed;
	currentPos.y = currentPos.y < float(GameInstance::GetInstance().GetScreenHeight() + GameInstance::GetInstance().GetScreenMinY()) - m_pOwningGameObject.lock()->GetTransform().GetHeight() ? currentPos.y : float(GameInstance::GetInstance().GetScreenHeight() + GameInstance::GetInstance().GetScreenMinY()) - m_pOwningGameObject.lock()->GetTransform().GetHeight();
	m_pOwningGameObject.lock()->GetTransform().SetPosition(currentPos);
}

void Controller::Shoot(Shooter shooter) const
{
	const float size{ 64 };
	glm::vec3 currentPos{ m_pOwningGameObject.lock()->GetTransform().GetPosition() };
	currentPos.y -= size + 1;
	const std::shared_ptr<StreamEngine::Scene> activeScene{ StreamEngine::SceneManager::GetInstance().GetActiveScene() };
	CreateBullet(activeScene, currentPos, size, shooter);
}
