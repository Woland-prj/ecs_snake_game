#ifndef TEXTRENDERSYSTEM_H
#define TEXTRENDERSYSTEM_H
#include "Components.h"
#include "system/System.h"

#include <sys/ttycom.h>

namespace game
{
class TextRenderSystem final : public ecs_engine::system::System<Position, Symbol>
{
	using Screen = std::vector<std::vector<wchar_t>>;

	enum class LineType
	{
		Horizontal,
		Vertical
	};

private:
	std::wstring m_clear = L"\033[2J\033[1;1H";
	std::wstring m_hideCursor = L"\033[?25l";
	std::wstring m_moveTop = L"\033[H";
	size_t m_fieldSize;
	[[nodiscard]] Position GetGlobalCoords(Position baseCoords) const;
	void Render(const Screen& screen) const;
	void DrawField(Screen& screen) const;
	void DrawLine(Screen& screen, LineType type, Position start, size_t length, Symbol symbol) const;
	void DrawDot(Screen& screen, Position position, Symbol symbol) const;
	[[nodiscard]] static winsize GetWinsize();

public:
	explicit TextRenderSystem(size_t fieldSize);
	void Init() override;
	void Tick() override;
};
} // namespace game

#endif // TEXTRENDERSYSTEM_H
