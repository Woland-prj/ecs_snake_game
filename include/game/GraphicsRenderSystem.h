#ifndef GRAPHICSRENDERSYSTEM_H
#define GRAPHICSRENDERSYSTEM_H

#include "Components.h"
#include "Events.h"
#include "system/System.h"
#include <SFML/Graphics.hpp>

namespace game
{
static constexpr int BASIC_CELL_SIZE = 20;
static constexpr auto WIN_TITLE = "ECS Snake";
static constexpr int FRAME_LIMIT = 60;

class GraphicsRenderSystem final : public ecs_engine::system::System<Position, Color, Texture>
{
public:
	explicit GraphicsRenderSystem(size_t fieldSize);

	void Init() override;

	void Tick() override;

private:
	size_t m_fieldSize;
	const int m_cellSize = BASIC_CELL_SIZE;
	sf::RenderWindow m_window;

	void DrawField();

	void DrawDot(const Position& position, const Color& color);

	void DrawTexturedDot(const Position& position, const Texture& texture);
};

} // namespace game

#endif //GRAPHICSRENDERSYSTEM_H
