#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include "Components.h"
#include "system/System.h"

namespace game
{
class InputSystem final : public ecs_engine::system::System<SnakeHead, Direction>
{
public:
	InputSystem() = default;
	void Init() override;
	void Tick() override;
};
} // namespace game

#endif // INPUTSYSTEM_H
