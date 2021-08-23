#include "stdafx.h"
#include "PlayerBehavior.h"

#include <utility>

#include "GameInstance.h"
#include "GameObject.h"
#include "GameOverBehavior.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"

PlayerBehavior::PlayerBehavior(const std::weak_ptr<StreamEngine::GameObject>& pOwningGameObject, Player player, std::weak_ptr<Controller> pController)
	:BaseComponent(false, pOwningGameObject),
	m_HasDied(),
	m_DeadTime(),
	m_Player(player),
	m_pController(std::move(pController))
{
}

void PlayerBehavior::Update(float deltaTime)
{
	if (m_HasDied)
	{
		m_DeadTime -= deltaTime;
		if (m_DeadTime <= 0)
		{
			m_HasDied = false;
			m_pOwningGameObject.lock()->SetIsVisual(true);
		}
	}
}

void PlayerBehavior::LateUpdate(float)
{
	if (m_pOwningGameObject.lock()->GetToRemove())
	{
		StreamEngine::SceneManager::GetInstance().SetActiveScene("GameOverScreen");
		//StreamEngine::SceneManager::GetInstance().GetScene("GameOverScreen")->GetObjectByName("gameOverBehavior")->GetComponent<GameOverBehavior>()->SetRemainingTime(5000);
		//StreamEngine::SceneManager::GetInstance().GetScene("GameOverScreen")->GetObjectByName("gameOverBehavior")->GetComponent<GameOverBehavior>()->ResetScenes();
	}
}

void PlayerBehavior::Die()
{
	if (!m_HasDied)
	{
		m_HasDied = true;
		m_DeadTime = 5000;
		if (!GameInstance::GetInstance().RemoveLife(m_Player))
		{
			//m_pOwningGameObject.lock()->SetIsActive(false);
			m_pOwningGameObject.lock()->SetToRemove(true);
			StreamEngine::SceneManager::GetInstance().GetScene("GameOverScreen")->GetObjectByName("shotsFired")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(GameInstance::GetInstance().GetShotsFired()));
			StreamEngine::SceneManager::GetInstance().GetScene("GameOverScreen")->GetObjectByName("NumberOfHits")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(GameInstance::GetInstance().GetHits()));
			StreamEngine::SceneManager::GetInstance().GetScene("GameOverScreen")->GetObjectByName("hitMissPercentage")->GetComponent<StreamEngine::TextComponent>()->SetText(std::to_string(float(GameInstance::GetInstance().GetShotsFired()) / (float(GameInstance::GetInstance().GetHits())+0.0001f)));
		}
		else
		{
			m_pOwningGameObject.lock()->SetIsVisual(false);
		}
	}
}

void PlayerBehavior::MoveRight() const
{
	if (!m_HasDied)
	{
		if (const auto pController = m_pController.lock())
		{
			pController->MoveRight();
		}
	}
}

void PlayerBehavior::MoveLeft() const
{
	if (!m_HasDied)
	{
		if (const auto pController = m_pController.lock())
		{
			pController->MoveLeft();
		}
	}
}

void PlayerBehavior::Shoot(Shooter shooter) const
{
	if (!m_HasDied)
	{
		if (const auto pController = m_pController.lock())
		{
			pController->Shoot(shooter);
			GameInstance::GetInstance().AddShotFired();
		}
	}
}
