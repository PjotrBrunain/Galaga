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

	Point operator*(const Point& rhs) const
	{
		return Point{ x * rhs.x, y * rhs.y };
	}
	int x;
	int y;
};

inline Point operator*(const float x, const Point& rhs)
{
	return Point{ int(x * float(rhs.x)), int(x * float(rhs.y)) };
}