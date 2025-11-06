#include "InitSystem.h"
#include "Components.h"

namespace game
{
void InitSystem::Init()
{
	const auto seg3 = EntityManager()->CreateEntity<SnakeSegment, Position, Symbol, Color>(
		SnakeSegment{},
		Position{ m_fieldSize / 2 - 2, m_fieldSize / 2 },
		Symbol{ SEGMENT_CHAR },
		Color(SNAKE_COLOR)
		);

	const auto seg2 = EntityManager()->CreateEntity<SnakeSegment, NextSegment, Position, Symbol, Color>(
		SnakeSegment{},
		NextSegment{ seg3 },
		Position{ m_fieldSize / 2 - 1, m_fieldSize / 2 },
		Symbol{ SEGMENT_CHAR },
		Color(SNAKE_COLOR)
		);

	EntityManager()->CreateEntity<SnakeHead, SnakeSegment, NextSegment, Position, Direction, Symbol, Color>(
		SnakeHead{},
		SnakeSegment{},
		NextSegment{ seg2 },
		Position{ m_fieldSize / 2, m_fieldSize / 2 },
		Direction{ 1, 0 },
		Symbol{ HEAD_RIGHT_CHAR },
		Color(SNAKE_COLOR)
		);
}

void InitSystem::Tick()
{
}
} // namespace game
