#include "stdafx.h"
#include "ScoreObserver.h"
#include "Enums.h"
#include "GameInstance.h"

void ScoreObserver::OnNotify(const std::shared_ptr<StreamEngine::GameObject>&, int event)
{
	int score{};

	switch (PointEvent(event))
	{
	case PointEvent::Zako: 
		score = 50;
		break;
	case PointEvent::ZakoBomb: 
		score = 100;
		break;
	case PointEvent::Goei: 
		score = 80;
		break;
	case PointEvent::GoeiBomb: 
		score = 160;
		break;
	case PointEvent::Galaga: 
		score = 150;
		break;
	case PointEvent::GalagaBomb: 
		score = 400;
		break;
	}

	GameInstance::GetInstance().AddPoints(score);
}
