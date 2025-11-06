#ifndef GROWINGSYSTEM_H
#define GROWINGSYSTEM_H
#include "Components.h"
#include "system/System.h"

namespace game
{
class GrowingSystem final : public ecs_engine::system::System<SnakeSegment, Position>
{
public:
	GrowingSystem(size_t fieldSize)
		: m_fieldSize(fieldSize) {};
	void Init() override;
	void Tick() override;

private:
	void OnGrow() const;
	size_t m_fieldSize;
};
} // namespace game

#endif // GROWINGSYSTEM_H
