#pragma once
#include <deque>
#include <vector>

#include "BaseComponent.h"
#include "Enums.h"
#include "Structs.h"

class Controller;

class BasicEnemyBehavior final : public StreamEngine::BaseComponent
{
public:
	explicit BasicEnemyBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject, std::shared_ptr<Controller> pController, const std::vector<Point>& startingBezierPoints);
	virtual ~BasicEnemyBehavior() = default;

	void Update(float deltaTime) override;

	void Die();

	BasicEnemyBehavior(const BasicEnemyBehavior&) = delete;
	BasicEnemyBehavior(BasicEnemyBehavior&&) noexcept = delete;
	BasicEnemyBehavior& operator=(const BasicEnemyBehavior&) = delete;
	BasicEnemyBehavior& operator=(BasicEnemyBehavior&&) noexcept = delete;
private:
	std::shared_ptr<Controller> m_pZakoController;

	std::deque<Point> m_StartingPath;
	std::vector<Point> m_BombingPath;

	std::vector<Point> m_BombingBezierPoints;

	size_t m_BombingIndex;

	const float m_Precision;

	void CalculateBezierPath(const std::vector<Point>& bezierPoints, std::deque<Point>& pointContainer);
	void CalculateBezierPath(const std::vector<Point>& bezierPoints, std::vector<Point>& pointContainer);
	static int GetPoint(int n1, int n2, float perc);
	EnemyState m_EnemyState;

	bool m_HasDied;
};
