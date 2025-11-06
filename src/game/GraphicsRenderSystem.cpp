#include "GraphicsRenderSystem.h"

namespace game
{

GraphicsRenderSystem::GraphicsRenderSystem(const size_t fieldSize)
	: m_fieldSize(fieldSize)
{
}

void GraphicsRenderSystem::Init()
{
	auto windowSize = static_cast<unsigned int>(m_fieldSize * m_cellSize);
	m_window.create(sf::VideoMode({ windowSize, windowSize }), "ECS Snake");
	m_window.setFramerateLimit(60);
	EventBus()->Publish(WindowCreatedEvent(m_window));
}

void GraphicsRenderSystem::Tick()
{
	m_window.clear(sf::Color::Black);
	DrawField();

	for (const auto entityId : Entities())
	{
		const Position* position = ComponentManager()->GetComponent<Position>(entityId);
		const Color* color = ComponentManager()->GetComponent<Color>(entityId);
		if (position && color)
			DrawDot(*position, *color);
	}

	m_window.display();
}

void GraphicsRenderSystem::DrawField()
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color(FIELD_COLOR.r, FIELD_COLOR.g, FIELD_COLOR.b));

	// horizontal
	for (size_t y = 0; y <= m_fieldSize; ++y)
	{
		line.setSize({ static_cast<float>(m_fieldSize * m_cellSize), 1 });
		line.setPosition({ 0, static_cast<float>(y * m_cellSize) });
		m_window.draw(line);
	}

	// vertical
	for (size_t x = 0; x <= m_fieldSize; ++x)
	{
		line.setSize({ 1, static_cast<float>(m_fieldSize * m_cellSize) });
		line.setPosition({ static_cast<float>(x * m_cellSize), 0 });
		m_window.draw(line);
	}
}

void GraphicsRenderSystem::DrawDot(const Position& position, const Color& color)
{
	if (position.x >= m_fieldSize || position.y >= m_fieldSize)
		return;

	sf::RectangleShape cell({ static_cast<float>(m_cellSize) - 1, static_cast<float>(m_cellSize) - 1 });
	cell.setPosition({ static_cast<float>(position.x * m_cellSize) + 1, static_cast<float>(position.y * m_cellSize) + 1 });
	cell.setFillColor(sf::Color(color.r, color.g, color.b));
	m_window.draw(cell);
}

} // namespace game