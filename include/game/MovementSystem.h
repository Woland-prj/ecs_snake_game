#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H
#include "Components.h"
#include "system/System.h"

namespace game
{
class MovementSystem final : public ecs_engine::system::System<SnakeSegment, NextSegment, Direction, Position>
{
public:
	MovementSystem() = default;
	void Init() override;
	void Tick() override;

private:
	void OnCollide();
	bool m_isPause = false;
};
} // namespace game

#endif // MOVEMENTSYSTEM_H
