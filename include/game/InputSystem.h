#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include "system/System.h"
#include "Components.h"

namespace game
{
class InputSystem final : public ecs_engine::system::System<SnakeHead, Direction>
{
public:
	InputSystem() = default;
	void Init() override;
	void Tick() override;
};
}


#endif //INPUTSYSTEM_H
