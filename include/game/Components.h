#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "entity/EntityIdPool.h"

namespace game
{
struct Position
{
	int x;
	int y;
};

struct Direction
{
	int dx;
	int dy;
};

struct Symbol
{
	char ch;
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
}

#endif //COMPONENTS_H
