#ifndef TEXTRENDERSYSTEM_H
#define TEXTRENDERSYSTEM_H
#include "Components.h"
#include "system/System.h"

#include <chrono>
#include <sys/ttycom.h>

namespace game
{
class TextRenderSystem final : public ecs_engine::system::System<Position, Symbol>
{
private:
	size_t m_fieldSize;
	std::vector<std::vector<char>> m_field;

public:
	explicit TextRenderSystem(size_t fieldSize);
	void Init() override;
	void Tick() override;
	void Render() const;
	[[nodiscard]] static winsize GetWinsize();
};
} // namespace game

#endif // TEXTRENDERSYSTEM_H
