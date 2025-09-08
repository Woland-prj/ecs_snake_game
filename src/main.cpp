#include "Engine.h"
#include <chrono>
#include "system/System.h"
#define FIELD_SIZE 5
#define MAX_ENTITY 30

struct Position
{
	int x;
	int y;
};

struct Symbol
{
	char ch;
};

class TextRenderSystem final : public ecs_engine::system::System<Position, Symbol>
{
private:
	size_t m_fieldSize;
	std::vector<std::vector<char>> m_field;
	std::chrono::steady_clock::time_point m_lastTick;
	const std::chrono::milliseconds m_frameTime{ 10 };

public:
	TextRenderSystem()
		: m_fieldSize(FIELD_SIZE), m_field(m_fieldSize, std::vector<char>(m_fieldSize, ' '))
	{
	};

	explicit TextRenderSystem(const size_t fieldSize)
		: m_fieldSize(fieldSize), m_field(m_fieldSize, std::vector<char>(m_fieldSize, ' '))
	{
	};

	void Init() override
	{
		EntityManager()->CreateEntity<Position, Symbol>(Position{ 4, 2 }, Symbol{ '@' });
		EntityManager()->CreateEntity<Position, Symbol>(Position{ 8, 3 }, Symbol{ 'x' });
		EntityManager()->CreateEntity<Position, Symbol>(Position{ 6, 4 }, Symbol{ '+' });
		m_lastTick = std::chrono::steady_clock::now();
	}

	void Tick() override
	{
		const auto now = std::chrono::steady_clock::now();

		if (const auto delta = now - m_lastTick; delta < m_frameTime)
			return;

		m_lastTick = now;

		for (const auto& entityId : Entities())
		{
			const auto position = m_componentManager->GetComponent<Position>(entityId);
			const auto symbol = m_componentManager->GetComponent<Symbol>(entityId);
			if (position->x < m_fieldSize && position->y < m_fieldSize)
				m_field[position->x][position->y] = symbol->ch;
		}

		Render();
	}

	void Render() const
	{
		std::cout << "\033[2J\033[1;1H";
		for (auto& row : m_field)
		{
			for (const auto& pos : row)
			{
				std::cout << pos;
			}
			std::cout << "\n";
		}
		std::cout << std::flush;
	}
};

int main(int argc, char* argv[])
{
	ecs_engine::Engine engine(MAX_ENTITY);
	engine.RegisterComponents<Position, Symbol>();
	engine.AppendSystem<TextRenderSystem>(20);
	engine.Run();
}
