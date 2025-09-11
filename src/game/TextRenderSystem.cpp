#include "TextRenderSystem.h"

#include "Components.h"
#include <cstdio>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

namespace game
{
Position TextRenderSystem::GetGlobalCoords(Position baseCoords)
{
	int offset_y = (GetWinsize().ws_row - m_fieldSize) / 2;
	int offset_x = (GetWinsize().ws_col - m_fieldSize) / 2;

	return Position{
		.x = baseCoords.x + offset_x,
		.y = baseCoords.y + offset_y
	};
}

TextRenderSystem::TextRenderSystem(const size_t fieldSize)
	: m_fieldSize(fieldSize) {};

void TextRenderSystem::Init()
{
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	std::wcout << m_clear;
	std::wcout << m_hideCursor;
}

void TextRenderSystem::Tick()
{
	Screen screen(GetWinsize().ws_row, std::vector<wchar_t>(GetWinsize().ws_col, L' '));

	DrawField(screen);

	for (const auto& entityId : Entities())
	{
		const Position* position = ComponentManager()->GetComponent<Position>(entityId);
		const auto symbol = ComponentManager()->GetComponent<Symbol>(entityId);
		DrawDot(screen, *position, *symbol);
	}

	Render(screen);
}

void TextRenderSystem::Render(const Screen& screen)
{
	static Screen oldScreen(screen.size(), std::vector<wchar_t>(screen[0].size(), L' '));
	std::wcout << m_moveTop;

	for (size_t y = 0; y < screen.size(); y++)
	{
		for (size_t x = 0; x < screen[y].size(); x++)
		{
			if (screen[y][x] != oldScreen[y][x])
			{
				std::wcout << L"\033[" << (y + 1) << ";" << (x + 1) << "H" << screen[y][x];
			}
		}
	}
	oldScreen = screen;
	std::wcout << std::flush;
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

void TextRenderSystem::DrawLine(Screen& screen, LineType type, Position start, size_t length, Symbol symbol)
{
	if (type == LineType::Horizontal)
	{
		for (size_t i = 0; i < length; i++)
		{
			DrawDot(screen, Position{ start.x + i, start.y }, symbol);
		}
	}
	if (type == LineType::Vertical)
	{
		for (size_t i = 0; i < length; i++)
		{
			DrawDot(screen, Position{ start.x, start.y + i }, symbol);
		}
	}
}

void TextRenderSystem::DrawDot(Screen& screen, Position position, Symbol symbol)
{
	auto coord = GetGlobalCoords(position);
	if (coord.y < 0 || coord.y >= screen.size())
		return;
	if (coord.x < 0 || coord.x >= screen[coord.y].size())
		return;
	if (position.x >= m_fieldSize || position.y >= m_fieldSize)
		return;
	screen[coord.y][coord.x] = symbol.ch;
}

void TextRenderSystem::DrawField(Screen& screen)
{
	DrawLine(screen, LineType::Horizontal, Position{ 1, 0 }, m_fieldSize - 2, Symbol{ L'─' });
	DrawLine(screen, LineType::Vertical, Position{ 0, 1 }, m_fieldSize - 2, Symbol{ L'│' });
	DrawLine(screen, LineType::Horizontal, Position{ 1, m_fieldSize - 1 }, m_fieldSize - 2, Symbol{ L'─' });
	DrawLine(screen, LineType::Vertical, Position{ m_fieldSize - 1, 1 }, m_fieldSize - 2, Symbol{ L'│' });
	DrawDot(screen, Position{ 0, 0 }, Symbol{ L'┌' });
	DrawDot(screen, Position{ m_fieldSize - 1, 0 }, Symbol{ L'┐' });
	DrawDot(screen, Position{ 0, m_fieldSize - 1 }, Symbol{ L'└' });
	DrawDot(screen, Position{ m_fieldSize - 1, m_fieldSize - 1 }, Symbol{ L'┘' });
}

} // namespace game
