#include "stdafx.h"
#include "GameOverBehavior.h"
#include "SceneManager.h"

#include <utility>

#include "LoadFunction.h"

GameOverBehavior::GameOverBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningObject)
	:BaseComponent(false, std::move(pOwningObject)),
	m_RemainingTime()
{
}

void GameOverBehavior::Update(float)
{
	//if (m_RemainingTime <=0)
	//{
	//	StreamEngine::SceneManager::GetInstance().SetActiveScene("StartScreen");
	//}
	//else
	//{
	//	m_RemainingTime -= deltaTime;
	//}
}

void GameOverBehavior::SetRemainingTime(float time)
{
	m_RemainingTime = time;
}

void GameOverBehavior::ResetScenes()
{
	const std::shared_ptr<StreamEngine::GameObject> fpsCounter{ StreamEngine::SceneManager::GetInstance().GetScene("Level1")->GetObjectByName("fpsComponent") };
	StreamEngine::SceneManager::GetInstance().RemoveScene("Level1");
	StreamEngine::SceneManager::GetInstance().RemoveScene("Level2");
	StreamEngine::SceneManager::GetInstance().RemoveScene("Level3");
	LoadLevel("../Data/Level1.json", fpsCounter, "Level1");
	LoadLevel("../Data/Level2.json", fpsCounter, "Level2");
	LoadLevel("../Data/Level3.json", fpsCounter, "Level3");
}
