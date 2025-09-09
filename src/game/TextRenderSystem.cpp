#include "TextRenderSystem.h"

#include "Components.h"
#include "system/System.h"
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>

#include <chrono>

namespace game
{

TextRenderSystem::TextRenderSystem(const size_t fieldSize)
	: m_fieldSize(fieldSize), m_field(std::vector<std::vector<char>>(GetWinsize().ws_row, std::vector<char>(GetWinsize().ws_col, ' ')))
{
};

void TextRenderSystem::Init()
{
	EntityManager()->CreateEntity<Position, Symbol>(Position{ 4, 2 }, Symbol{ '@' });
	EntityManager()->CreateEntity<Position, Symbol>(Position{ 8, 3 }, Symbol{ 'x' });
	EntityManager()->CreateEntity<Position, Symbol>(Position{ 6, 4 }, Symbol{ '+' });
}

void TextRenderSystem::Tick()
{

	for (const auto& entityId : Entities())
	{
		const Position* position = ComponentManager()->GetComponent<Position>(entityId);
		const auto symbol = ComponentManager()->GetComponent<Symbol>(entityId);
		if (position->x < m_fieldSize && position->y < m_fieldSize)
			m_field[position->x][position->y] = symbol->ch;
	}

	Render();
}

void TextRenderSystem::Render() const
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

winsize TextRenderSystem::GetWinsize()
{
	struct winsize w{};
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
	{
		perror("ioctl");
	}
	return w;
}

}