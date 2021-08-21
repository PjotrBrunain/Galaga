#pragma once
#include <vector>

#include "BaseComponent.h"

namespace StreamEngine
{
	class Observer;
}

class SubjectComponent final : public StreamEngine::BaseComponent
{
public:
	explicit SubjectComponent(const std::weak_ptr<StreamEngine::GameObject>& pOwningObject);
	virtual ~SubjectComponent() = default;

	void AddObserver(const std::shared_ptr<StreamEngine::Observer> pObserver);
	void RemoveObserver(const std::shared_ptr<StreamEngine::Observer> pObserver);
	void Notify(const std::shared_ptr<StreamEngine::GameObject>& pEntity, int event);

	SubjectComponent(const SubjectComponent&) = delete;
	SubjectComponent(SubjectComponent&&) noexcept = delete;
	SubjectComponent& operator=(const SubjectComponent&) = delete;
	SubjectComponent& operator=(SubjectComponent&&) noexcept = delete;
private:
	std::vector<std::shared_ptr<StreamEngine::Observer>> m_pObservers;
};
