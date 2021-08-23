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
	explicit BasicEnemyBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject, std::weak_ptr<Controller> pController, const std::vector<Point>& startingBezierPoints, const EnemyType& enemyType, float startDelay);
	virtual ~BasicEnemyBehavior() = default;

	void Update(float deltaTime) override;

	void Die();

	BasicEnemyBehavior(const BasicEnemyBehavior&) = delete;
	BasicEnemyBehavior(BasicEnemyBehavior&&) noexcept = delete;
	BasicEnemyBehavior& operator=(const BasicEnemyBehavior&) = delete;
	BasicEnemyBehavior& operator=(BasicEnemyBehavior&&) noexcept = delete;
private:
	std::weak_ptr<Controller> m_pController;

	std::deque<Point> m_StartingPath;
	std::vector<Point> m_BombingPath;

	std::vector<Point> m_BombingBezierPoints;

	size_t m_BombingIndex;

	const float m_Precision;

	void CalculateBezierPath(const std::vector<Point>& bezierPoints, std::deque<Point>& pointContainer) const;
	void CalculateBezierPath(const std::vector<Point>& bezierPoints, std::vector<Point>& pointContainer) const;
	static int GetPoint(int n1, int n2, float perc);
	EnemyState m_EnemyState;
	EnemyType m_EnemyType;

	bool m_HasDied;
	float m_StartDelay;
};
