#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace StreamEngine;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>&object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for (const auto& object : m_Objects)
	{
		if (object != nullptr)
		{
			object->Update(deltaTime);
		}
	}
}

void Scene::FixedUpdate(float deltaTime)
{
	for (const std::shared_ptr<GameObject>& object : m_Objects)
	{
		if (object != nullptr)
		{
			object->FixedUpdate(deltaTime);
		}
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (const std::shared_ptr<GameObject>& object : m_Objects)
	{
		if (object != nullptr)
		{
			object->LateUpdate(deltaTime);
		}
	}

	const auto it = std::remove_if(m_Objects.begin(), m_Objects.end(), [](std::shared_ptr<GameObject> object) { return object->GetToRemove(); });
	m_Objects.erase(it, m_Objects.end());
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		if (object != nullptr)
		{
			if (object->IsVisual())
			{
				object->Render();
			}
		}
	}
}

std::shared_ptr<GameObject> Scene::GetObjectByName(std::string name) const
{
	for (std::shared_ptr<GameObject> pObject : m_Objects)
	{
		if (pObject != nullptr)
		{
			if (pObject->GetName() == name)
			{
				return pObject;
			}
		}
	}

	return nullptr;
}

const std::vector<FlexibleCommand>& Scene::GetCommands() const
{
	return m_SceneCommands;
}

void Scene::AddCommand(const FlexibleCommand & command)
{
	m_SceneCommands.push_back(command);
}
