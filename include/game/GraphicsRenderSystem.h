#ifndef GRAPHICSRENDERSYSTEM_H
#define GRAPHICSRENDERSYSTEM_H

#include "Components.h"
#include "Events.h"
#include "system/System.h"
#include <SFML/Graphics.hpp>

namespace game
{
static constexpr int BASIC_CELL_SIZE = 20;

class GraphicsRenderSystem final : public ecs_engine::system::System<Position, Color>
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
};

} // namespace game

#endif //GRAPHICSRENDERSYSTEM_H
