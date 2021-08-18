#include "ZakoBehavior.h"

#include <utility>

#include "GameInstance.h"
#include "GameObject.h"

ZakoBehavior::ZakoBehavior(std::weak_ptr<StreamEngine::GameObject> pOwningGameObject,
	std::shared_ptr<Controller> pController)
	:BaseComponent(false, std::move(pOwningGameObject)),
	m_pZakoController(std::move(pController)),
	m_Precision(0.0075f),
	m_EnemyState(EnemyState::Starting)
{
}

void ZakoBehavior::Update(float deltaTime)
{
	//Point currentPos{ int(m_pOwningGameObject.lock()->GetTransform().GetPosition().x), int(m_pOwningGameObject.lock()->GetTransform().GetPosition().y) };
	if (!m_Path.empty())
	{
		m_pOwningGameObject.lock()->GetTransform().SetPosition(float(m_Path[0].x), float(m_Path[0].y), 1.f);
		m_Path.pop_front();
	}
	else
	{
		const auto& gameInstance{ GameInstance::GetInstance() };
		switch (m_EnemyState)
		{
		case EnemyState::Starting: 
			CalculateBezierPath(Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), gameInstance.GetScreenMinY() },
				Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.3f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() },
				Point{ gameInstance.GetScreenMinX(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() },
				Point{ int(0.5f * float(gameInstance.GetScreenWidth())) + gameInstance.GetScreenMinX(), int(0.6f * float(gameInstance.GetScreenHeight())) + gameInstance.GetScreenMinY() });
			break;
		case EnemyState::Bombing: break;
		case EnemyState::Stationary: break;
		}
	}
	deltaTime++;
}

void ZakoBehavior::CalculateBezierPath(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
{
	for (float i = 0; i < 1; i += m_Precision)  // NOLINT(cert-flp30-c)
	{
		const int xa{ GetPoint(point1.x, point2.x, i) };
		const int ya{ GetPoint(point1.y, point2.y, i) };
		const int xb{ GetPoint(point2.x, point3.x, i) };
		const int yb{ GetPoint(point2.y, point3.y, i) };
		const int xc{ GetPoint(point3.x, point4.x, i) };
		const int yc{ GetPoint(point3.y, point4.y, i) };

		const int xm{ GetPoint(xa, xb, i) };
		const int ym{ GetPoint(ya, yb, i) };
		const int xn{ GetPoint(xb, xc, i) };
		const int yn{ GetPoint(yb, yc, i) };

		const int x{ GetPoint(xm, xn, i) };
		const int y{ GetPoint(ym, yn, i) };

		m_Path.push_back(Point{ x,y });
	}
}

int ZakoBehavior::GetPoint(const int n1, const int n2, const float perc)
{
	const int difference = n2 - n1;
	return int(float(n1) + (float(difference) * perc));
}
