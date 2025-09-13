#include "InitSystem.h"
#include "Components.h"

namespace game
{
void InitSystem::Init()
{
	auto seg3 = EntityManager()->CreateEntity<SnakeSegment, Position, Symbol>(
		SnakeSegment{},
		Position{ m_fieldSize / 2 - 2, m_fieldSize / 2 },
		Symbol{ SegmentChar });

	auto seg2 = EntityManager()->CreateEntity<SnakeSegment, NextSegment, Position, Symbol>(
		SnakeSegment{},
		NextSegment{ seg3 },
		Position{ m_fieldSize / 2 - 1, m_fieldSize / 2 },
		Symbol{ SegmentChar });

	EntityManager()->CreateEntity<SnakeHead, SnakeSegment, NextSegment, Position, Direction, Symbol>(
		SnakeHead{},
		SnakeSegment{},
		NextSegment{ seg2 },
		Position{ m_fieldSize / 2, m_fieldSize / 2 },
		Direction{ 1, 0 },
		Symbol{ HeadRightChar });
}
void InitSystem::Tick() {}
} // namespace game
