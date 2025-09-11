#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "entity/EntityIdPool.h"

namespace game
{
struct Position
{
	size_t x;
	size_t y;
};

struct Direction
{
	int dx;
	int dy;
};

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

struct Collidable
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
