#ifndef INITSYSTEM_H
#define INITSYSTEM_H
#include "Components.h"
#include "system/System.h"

namespace game
{
class InitSystem final : public ecs_engine::system::System<SnakeSegment, NextSegment, Direction, Position, Symbol>
{
public:
	InitSystem(size_t fieldSize)
		: m_fieldSize(fieldSize) {};
	void Init() override;
	void Tick() override;

private:
	size_t m_fieldSize;
};
} // namespace game

#endif // INITSYSTEM_H
