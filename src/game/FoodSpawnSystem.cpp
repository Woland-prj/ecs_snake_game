#include "FoodSpawnSystem.h"
#include "Components.h"
#include "entity/EntityIdPool.h"
#include <random>
#include <vector>

namespace game
{
void FoodSpawnSystem::Init()
{
}

void FoodSpawnSystem::Tick()
{
	const auto segments = EntityManager()->GetEntitiesByComponents<SnakeSegment>();
	if (const auto foods = Entities(); foods.empty())
	{
		auto spawnPos = GetSpawnPosition(segments);
		auto food = EntityManager()->CreateEntity<Food, Position, Symbol, Color, Texture>(
			Food{},
			Position(spawnPos),
			Symbol{ FOOD_CHAR },
			Color(FOOD_COLOR),
			Texture{ FOOD_TEXTURE });
	}
}

Position FoodSpawnSystem::GetSpawnPosition(const std::vector<ecs_engine::entity::EntityId>& segments)
{
	while (true)
	{
		Position pos{ m_dist(m_rng), m_dist(m_rng) };
		bool conflict = false;
		for (const auto seg : segments)
		{
			if (const auto* segPos = ComponentManager()->GetComponent<Position>(seg))
			{
				if (pos == *segPos)
				{
					conflict = true;
					break;
				}
			}
		}
		if (!conflict)
			return pos;
	}
}
} // namespace game
