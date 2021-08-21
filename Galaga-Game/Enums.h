#pragma once

enum class GameMode
{
	SinglePlayer,
	Coop,
	Versus
};

enum class EnemyState
{
	Starting,
	Bombing,
	Stationary
};

enum class PointEvent
{
	Zako = 0,
	ZakoBomb = 1,
	Goei = 2,
	GoeiBomb = 3,
	Galaga = 4,
	GalagaBomb = 5
};