#ifndef GRAPHICSINPUTSYSTEM_H
#define GRAPHICSINPUTSYSTEM_H

#include "Components.h"
#include "system/System.h"
#include "Events.h"
#include <SFML/Graphics.hpp>
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

class GraphicsInputSystem final : public ecs_engine::system::System<SnakeHead, Direction>
{
public:
	GraphicsInputSystem() = default;

	void Init() override;

	void Tick() override;

private:
	void OnWindowCreated(const WindowCreatedEvent& evt);

	void OnCollide();

	sf::RenderWindow* m_window = nullptr;
	bool m_isPause = false;

	const std::unordered_map<Dir, Direction> m_dirMap = {
		{ Dir::UP, Direction{ 0, -1 } },
		{ Dir::DOWN, Direction{ 0, 1 } },
		{ Dir::LEFT, Direction{ -1, 0 } },
		{ Dir::RIGHT, Direction{ 1, 0 } }
	};
};
} // namespace game

#endif // GRAPHICSINPUTSYSTEM_H