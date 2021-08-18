#pragma once

struct Rect
{
	float bottom;
	float left;
	float width;
	float height;
};

enum class Move
{
	Up = 0,
	Down = 6,
	Left = 2,
	Right = 4
};

struct OffsetTileCoords
{
	int col;
	int row;
};

struct Point
{
	bool operator!=(const Point& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}
	int x;
	int y;
};
