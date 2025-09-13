#include "FoodSpawnSystem.h"
#include "Components.h"
#include "entity/EntityIdPool.h"
#include <random>
#include <vector>

namespace game
{
void FoodSpawnSystem::Init() {}
void FoodSpawnSystem::Tick()
{
	auto segments = EntityManager()->GetEntitiesByComponents<SnakeSegment>();
	auto foods = Entities();
	if (foods.size() == 0)
	{
		auto spawnPos = GetSpawnPosition(segments);
		auto food = EntityManager()->CreateEntity<Food, Position, Symbol>(
			Food{},
			Position(spawnPos),
			Symbol{ FoodChar });
	}
}

Position FoodSpawnSystem::GetSpawnPosition(const std::vector<ecs_engine::entity::EntityId>& segments)
{
	Position spawnPos;
	bool found = false;
	while (!found)
	{
		auto pos = Position{ m_dist(m_rng), m_dist(m_rng) };
		for (const auto seg : segments)
		{
			Position* segPos = ComponentManager()->GetComponent<Position>(seg);
			if (pos.x == segPos->x && pos.y == segPos->y)
			{
				found = false;
				break;
			}
		}
		if (!found)
		{
			spawnPos = pos;
			found = true;
		}
	}
	return spawnPos;
}
} // namespace game
