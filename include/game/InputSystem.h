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

private:
	void OnCollide();
	bool m_isPause = false;
};
} // namespace game

#endif // INPUTSYSTEM_H
