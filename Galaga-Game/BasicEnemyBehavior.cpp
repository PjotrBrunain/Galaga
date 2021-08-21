#include "BasicEnemyBehavior.h"

#include <chrono>
#include <utility>
#include <random>

#include "GameInstance.h"
#include "GameObject.h"

BasicEnemyBehavior::BasicEnemyBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject,
	std::shared_ptr<Controller> pController, const std::vector<Point>& startingBezierPoints)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_pZakoController(std::move(pController)),
	m_BombingIndex(),
	m_Precision(0.0075f),
	m_EnemyState(EnemyState::Starting),
	m_HasDied()
{
	CalculateBezierPath(startingBezierPoints, m_StartingPath);

	auto& gameInstance = GameInstance::GetInstance();

	m_BombingBezierPoints = { 1 * startingBezierPoints.back(),
		Point{int(0.f * float(startingBezierPoints.back().x)), int(0.4f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(5.f * float(startingBezierPoints.back().x)),int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(0.f * float(startingBezierPoints.back().x)), int(0.8f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(1.f * float(startingBezierPoints.back().x)), int(1.f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()}/*,
		Point{int(2.5f * float(startingBezierPoints.back().x)), int(0.8f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(0.1f * float(startingBezierPoints.back().x)), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(2.5f * float(startingBezierPoints.back().x)), int(0.4f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		1 * startingBezierPoints.back() */};

	CalculateBezierPath(m_BombingBezierPoints, m_BombingPath);

	m_BombingBezierPoints = { Point{int(1.f * float(startingBezierPoints.back().x)), int(1.f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(5.f * float(startingBezierPoints.back().x)), int(0.8f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(-5.f * float(startingBezierPoints.back().x)),int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		Point{int(5.f * float(startingBezierPoints.back().x)), int(0.4f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY()},
		1 * startingBezierPoints.back()
	};

	CalculateBezierPath(m_BombingBezierPoints, m_BombingPath);
}

void BasicEnemyBehavior::Update(float deltaTime)
{
	//Point currentPos{ int(m_pOwningGameObject.lock()->GetTransform().GetPosition().x), int(m_pOwningGameObject.lock()->GetTransform().GetPosition().y) };
	if (!m_StartingPath.empty())
	{
		m_pOwningGameObject.lock()->GetTransform().SetPosition(float(m_StartingPath[0].x), float(m_StartingPath[0].y), 1.f);
		m_StartingPath.pop_front();
	}
	else
	{

		switch (m_EnemyState)
		{
		case EnemyState::Starting:
			m_EnemyState = EnemyState::Stationary;
			break;
		case EnemyState::Bombing:
			if (m_BombingIndex != m_BombingPath.size() - 1)
			{
				m_pOwningGameObject.lock()->GetTransform().SetPosition(float(m_BombingPath[m_BombingIndex].x), float(m_BombingPath[m_BombingIndex].y), 1.f);
				m_BombingIndex++;
				m_BombingIndex = m_BombingIndex % m_BombingPath.size();
			}
			else
			{
				m_EnemyState = EnemyState::Stationary;
				m_BombingIndex = 0;
			}
			break;
		case EnemyState::Stationary:
			const unsigned int seed{ unsigned int(std::chrono::system_clock::now().time_since_epoch().count()) };
			std::minstd_rand0 generator(seed);
			const unsigned int rand{ generator() };
			if (rand % 500 == 0)
			{
				m_EnemyState = EnemyState::Bombing;
			}
			break;
		}
	}
	deltaTime++;
}

void BasicEnemyBehavior::Die()
{
	if (!m_HasDied)
	{
		m_HasDied = true;

	}
}

void BasicEnemyBehavior::CalculateBezierPath(const std::vector<Point>& bezierPoints, std::deque<Point>& pointContainer)
{
	for (float i = 0; i < 1; i += m_Precision)
	{
		std::vector<Point> points{ bezierPoints };
		std::vector<Point> calcPoints{};
		do
		{
			for (size_t j = 0; j < points.size() - 1; ++j)
			{
				calcPoints.push_back({ GetPoint(points[j].x, points[j + 1].x, i), GetPoint(points[j].y, points[j + 1].y,i) });
			}
			points = calcPoints;
			calcPoints.clear();
		} while (points.size() > 1);
		pointContainer.push_back(points[0]);
	}
}

void BasicEnemyBehavior::CalculateBezierPath(const std::vector<Point>& bezierPoints, std::vector<Point>& pointContainer)
{
	for (float i = 0; i < 1; i += m_Precision)
	{
		std::vector<Point> points{ bezierPoints };
		std::vector<Point> calcPoints{};
		do
		{
			for (size_t j = 0; j < points.size() - 1; ++j)
			{
				calcPoints.push_back({ GetPoint(points[j].x, points[j + 1].x, i), GetPoint(points[j].y, points[j + 1].y,i) });
			}
			points = calcPoints;
			calcPoints.clear();
		} while (points.size() > 1);
		pointContainer.push_back(points[0]);
	}
}

int BasicEnemyBehavior::GetPoint(const int n1, const int n2, const float perc)
{
	const int difference = n2 - n1;
	return int(float(n1) + (float(difference) * perc));
}
