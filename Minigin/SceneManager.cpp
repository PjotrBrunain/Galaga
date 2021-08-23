#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void StreamEngine::SceneManager::Update(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->Update(deltaTime);
}

void StreamEngine::SceneManager::FixedUpdate(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->FixedUpdate(deltaTime);
}

void StreamEngine::SceneManager::LateUpdate(const float deltaTime)
{
	m_Scenes[m_CurrentScene]->LateUpdate(deltaTime);
}

void StreamEngine::SceneManager::Render()
{
	m_Scenes[m_CurrentScene]->Render();
}

std::shared_ptr<StreamEngine::Scene> StreamEngine::SceneManager::GetScene(const std::string& name)
{
	return m_Scenes[name];
}

void StreamEngine::SceneManager::RemoveScene(const std::string& name)
{
	m_Scenes.erase(name);
}

void StreamEngine::SceneManager::SetActiveScene(std::string name)
{
	if (m_Scenes.find(name) != m_Scenes.end())
	{
		m_CurrentScene = name;
		InputManager::GetInstance().SetCommands(m_Scenes[name]->GetCommands());
	}
}

std::shared_ptr<StreamEngine::Scene> StreamEngine::SceneManager::GetActiveScene()
{
	return m_Scenes[m_CurrentScene];
}

std::shared_ptr<StreamEngine::Scene>& StreamEngine::SceneManager::CreateScene(const std::string& name)
{
	auto scene = std::shared_ptr<Scene>(std::make_shared<Scene>(name));
	m_Scenes.insert(std::make_pair(name, scene));
	return m_Scenes[name];
}
