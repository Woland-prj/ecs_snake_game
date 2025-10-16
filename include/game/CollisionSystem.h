#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
#include "Components.h"
#include "system/System.h"

namespace game
{
class CollisionSystem final : public ecs_engine::system::System<SnakeSegment, Position>
{
public:
	explicit CollisionSystem(const size_t fieldSize)
		: m_fieldSize(fieldSize) {};
	void Init() override;
	void Tick() override;

private:
	size_t m_fieldSize;
};
} // namespace game

#endif // COLLISIONSYSTEM_H
