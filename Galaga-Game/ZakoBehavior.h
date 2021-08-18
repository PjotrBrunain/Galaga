#pragma once
#include <deque>

#include "BaseComponent.h"
#include "Enums.h"
#include "Structs.h"

class Controller;

class ZakoBehavior final : public StreamEngine::BaseComponent
{
public:
	explicit ZakoBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject, std::shared_ptr<Controller> pController);
	virtual ~ZakoBehavior() = default;

	void Update(float deltaTime) override;

	ZakoBehavior(const ZakoBehavior&) = delete;
	ZakoBehavior(ZakoBehavior&&) noexcept = delete;
	ZakoBehavior& operator=(const ZakoBehavior&) = delete;
	ZakoBehavior& operator=(ZakoBehavior&&) noexcept = delete;
private:
	std::shared_ptr<Controller> m_pZakoController;

	std::deque<Point> m_Path;

	const float m_Precision;

	void CalculateBezierPath(const Point& point1, const Point& point2, const Point& point3, const Point& point4);
	static int GetPoint(int n1, int n2, float perc);

	EnemyState m_EnemyState;
};
