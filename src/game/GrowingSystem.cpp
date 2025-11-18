#include "GrowingSystem.h"
#include "Components.h"
#include "Events.h"
#include "entity/EntityIdPool.h"

namespace game
{
void GrowingSystem::Init()
{
	EventBus()->Subscribe<GrowingEvent>([this](const GrowingEvent& event) {
		OnGrow();
	});
}

void GrowingSystem::Tick()
{
}

void GrowingSystem::OnGrow() const
{
	const auto food = EntityManager()->GetEntitiesByComponents<Food>()[0];
	EntityManager()->DeleteEntity(food);
	const auto head = EntityManager()->GetEntitiesByComponents<SnakeHead>()[0];

	ecs_engine::entity::EntityId prevSegment{};
	ecs_engine::entity::EntityId currSegment = head;

	while (EntityManager()->HasComponent<NextSegment>(currSegment))
	{
		prevSegment = currSegment;
		currSegment = ComponentManager()->GetComponent<NextSegment>(currSegment)->next;
	}

	const auto* prevSegmentPos = ComponentManager()->GetComponent<Position>(prevSegment);
	const auto* tailSegmentPos = ComponentManager()->GetComponent<Position>(currSegment);

	const Direction tailDir(tailSegmentPos->x - prevSegmentPos->x, tailSegmentPos->y - prevSegmentPos->y);

	const auto newSeg = EntityManager()->CreateEntity<SnakeSegment, Position, Symbol, Color, Texture>(
		SnakeSegment{},
		Position{ tailSegmentPos->x + tailDir.dx, tailSegmentPos->y + tailDir.dy },
		Symbol{ SEGMENT_CHAR },
		Color(SNAKE_COLOR),
		Texture{ BODY_TEXTURE }
		);

	ComponentManager()->CreateComponent<NextSegment>(currSegment, NextSegment{ newSeg });
	EntityManager()->AppendComponent<NextSegment>(currSegment);
}
} // namespace game
