#include "GrowingSystem.h"
#include "Components.h"
#include "Events.h"
#include "entity/EntityIdPool.h"
#include <iostream>

namespace game
{
void GrowingSystem::Init()
{
	EventBus()->Subscribe<GrowingEvent>([this](const GrowingEvent& event) {
		OnGrow();
	});
}
void GrowingSystem::Tick() {}

void GrowingSystem::OnGrow()
{
	const auto food = EntityManager()->GetEntitiesByComponents<Food>()[0];
	EntityManager()->DeleteEntity(food);
	const auto head = EntityManager()->GetEntitiesByComponents<SnakeHead>()[0];

	ecs_engine::entity::EntityId prevSegment;
	ecs_engine::entity::EntityId currSegment = head;

	while (EntityManager()->HasComponent<NextSegment>(currSegment))
	{
		prevSegment = currSegment;
		currSegment = ComponentManager()->GetComponent<NextSegment>(currSegment)->next;
	}

	Position* prevSegmentPos = ComponentManager()->GetComponent<Position>(prevSegment);
	Position* tailSegmentPos = ComponentManager()->GetComponent<Position>(currSegment);

	Direction tailDir(tailSegmentPos->x - prevSegmentPos->x, tailSegmentPos->y - prevSegmentPos->y);

	auto newSeg = EntityManager()->CreateEntity<SnakeSegment, Position, Symbol>(
		SnakeSegment{},
		Position{ tailSegmentPos->x + tailDir.dx, tailSegmentPos->y + tailDir.dy },
		Symbol{ SegmentChar });

	ComponentManager()->CreateComponent<NextSegment>(currSegment, NextSegment{ newSeg });
	EntityManager()->AppendComponent<NextSegment>(currSegment);
}
} // namespace game
