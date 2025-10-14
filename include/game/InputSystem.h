#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include "Components.h"
#include "system/System.h"
#include <unordered_map>

namespace game
{
enum class Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class InputSystem final : public ecs_engine::system::System<SnakeHead, Direction>
{
public:
	InputSystem() = default;
	void Init() override;
	void Tick() override;

private:
	void OnCollide();
	static uint8_t ReadRawBytes(ssize_t count, char* buff);

	bool m_isPause = false;
	const std::unordered_map<Dir, Direction> m_dirMap = {
		{ Dir::UP, Direction{ 0, -1 } },
		{ Dir::DOWN, Direction{ 0, 1 } },
		{ Dir::LEFT, Direction{ -1, 0 } },
		{ Dir::RIGHT, Direction{ 1, 0 } }
	};

	constexpr static char Esc = '\033';

	constexpr static char WASD_UP = 'w';
	constexpr static char WASD_DOWN = 's';
	constexpr static char WASD_LEFT = 'a';
	constexpr static char WASD_RIGHT = 'd';

	constexpr static char ARROW_UP = 'A';
	constexpr static char ARROW_DOWN = 'B';
	constexpr static char ARROW_LEFT = 'D';
	constexpr static char ARROW_RIGHT = 'C';
};
} // namespace game

#endif // INPUTSYSTEM_H
