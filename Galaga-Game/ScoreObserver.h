#pragma once
#include "Observer.h"

class ScoreObserver : StreamEngine::Observer
{
public:

	void OnNotify(const std::shared_ptr<StreamEngine::GameObject>& pEntity, int event) override;
};
