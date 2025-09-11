#include "MovementSystem.h"
#include "Components.h"

namespace game
{
void MovementSystem::Init() {};

void MovementSystem::Tick()
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
	Direction* dir = ComponentManager()->GetComponent<Direction>(headId);

	Position prev = *headPos;
	headPos->x += dir->dx;
	headPos->y += dir->dy;

	ecs_engine::entity::EntityId currentId = headId;

	while (true)
	{
		if (!EntityManager()->HasComponent<NextSegment>(currentId))
			break;
		const NextSegment* next = ComponentManager()->GetComponent<NextSegment>(currentId);
		// if (!next || next->next == ecs_engine::entity::EntityId{})
		// 	break;
		currentId = next->next;
		Position* currentPos = ComponentManager()->GetComponent<Position>(currentId);
		Position temp = *currentPos;

		*currentPos = prev;

		prev = temp;
	}
}
} // namespace game
