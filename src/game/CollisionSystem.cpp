#include "CollisionSystem.h"
#include "Components.h"
#include "Events.h"

namespace game
{
void CollisionSystem::Init()
{
}

void CollisionSystem::Tick()
{
	ecs_engine::entity::EntityId headId{};
	for (const auto& entityId : Entities())
	{
		if (EntityManager()->HasComponent<SnakeHead>(entityId))
		{
			headId = entityId;
			break;
		}
	}
	if (!headId)
		return;

	Position* headPos = ComponentManager()->GetComponent<Position>(headId);

	auto foods = EntityManager()->GetEntitiesByComponents<Food, Position>();
	if (foods.size() != 0)
	{
		Position* foodPos = ComponentManager()->GetComponent<Position>(foods[0]);
		if (foodPos->x == headPos->x && foodPos->y == headPos->y)
		{
			EventBus()->Publish(GrowingEvent{});
		}
	}

	ecs_engine::entity::EntityId currentId = headId;

	if (headPos->x <= 0 || headPos->x >= m_fieldSize - 1 || headPos->y <= 0 || headPos->y >= m_fieldSize - 1)
	{
		EventBus()->Publish(CollisionEvent{});
		return;
	}

	while (true)
	{
		if (!EntityManager()->HasComponent<NextSegment>(currentId))
			break;
		const NextSegment* next = ComponentManager()->GetComponent<NextSegment>(currentId);
		currentId = next->next;
		Position* currentPos = ComponentManager()->GetComponent<Position>(currentId);
		if (currentPos->x == headPos->x && currentPos->y == headPos->y)
		{
			EventBus()->Publish(CollisionEvent());
			break;
		}
	}
}
} // namespace game
