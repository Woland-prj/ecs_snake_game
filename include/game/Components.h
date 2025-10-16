#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "entity/EntityIdPool.h"

#include <cstdint>

namespace game
{

constexpr wchar_t SegmentChar = L'●';
constexpr wchar_t HeadUpChar = L'▲';
constexpr wchar_t HeadDownChar = L'▼';
constexpr wchar_t HeadLeftChar = L'◀';
constexpr wchar_t HeadRightChar = L'▶';
constexpr wchar_t FieldChar = L'.';
constexpr wchar_t FoodChar = L'●';

struct Position
{
	size_t x;
	size_t y;
};

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

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
