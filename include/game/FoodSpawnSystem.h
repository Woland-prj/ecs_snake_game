#ifndef FOODSPAWNSYSTEM_H
#define FOODSPAWNSYSTEM_H
#include "Components.h"
#include "system/System.h"
#include <random>

namespace game
{
class FoodSpawnSystem final : public ecs_engine::system::System<Food, Position>
{
public:
	FoodSpawnSystem(size_t fieldSize)
		: m_fieldSize(fieldSize)
		, m_rng(m_dev())
		, m_dist(1, m_fieldSize - 2) {};
	void Init() override;
	void Tick() override;

private:
	Position GetSpawnPosition(const std::vector<ecs_engine::entity::EntityId>& segments);
	size_t m_fieldSize;
	std::random_device m_dev;
	std::mt19937 m_rng;
	std::uniform_int_distribution<std::mt19937::result_type> m_dist;
};
} // namespace game

#endif // FOODSPAWNSYSTEM_H
