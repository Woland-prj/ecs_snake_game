#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "entity/EntityIdPool.h"

#include <cstdint>

namespace game
{

constexpr wchar_t SEGMENT_CHAR = L'●';
constexpr wchar_t HEAD_UP_CHAR = L'▲';
constexpr wchar_t HEAD_DOWN_CHAR = L'▼';
constexpr wchar_t HEAD_LEFT_CHAR = L'◀';
constexpr wchar_t HEAD_RIGHT_CHAR = L'▶';
constexpr wchar_t FIELD_CHAR = L'.';
constexpr wchar_t FOOD_CHAR = L'●';

struct Position
{
	size_t x;
	size_t y;

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	};
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

constexpr auto SNAKE_COLOR = Color{ 0, 200, 100 };
constexpr auto FIELD_COLOR = Color{ 80, 80, 80 };
constexpr auto FOOD_COLOR = Color{ 230, 0, 0 };

struct Direction
{
	int dx{};
	int dy{};

	constexpr explicit Direction(const int x = 0, const int y = 0)
		: dx(x)
		  , dy(y)
	{
	}

	bool operator==(const Direction& other) const
	{
		return dx == other.dx && dy == other.dy;
	}

	bool operator!=(const Direction& other) const
	{
		return !(*this == other);
	}

	Direction operator+(const Direction& other) const
	{
		return Direction{ dx + other.dx, dy + other.dy };
	}
};

constexpr auto zeroDir = Direction{ 0, 0 };

struct Symbol
{
	wchar_t ch;
};

struct SnakeHead
{
};

struct SnakeSegment
{
};

struct NextSegment
{
	ecs_engine::entity::EntityId next{};
};

struct Growing
{
};

struct Food
{
};

struct Field
{
	size_t width{};
	size_t height{};
};
} // namespace game

#endif // COMPONENTS_H
