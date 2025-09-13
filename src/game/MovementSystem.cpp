#include "MovementSystem.h"
#include "Components.h"
#include "Events.h"
#include <iostream>
#include <ostream>

namespace game
{
void MovementSystem::Init()
{
	EventBus()->Subscribe<CollisionEvent>([this](const CollisionEvent& event) {
		OnCollide();
	});
};

void MovementSystem::OnCollide()
{
	m_isPause = true;
}

void MovementSystem::Tick()
{
	if (m_isPause)
		return;
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
		currentId = next->next;
		Position* currentPos = ComponentManager()->GetComponent<Position>(currentId);
		Position temp = *currentPos;

		*currentPos = prev;

		prev = temp;
	}
}
} // namespace game
