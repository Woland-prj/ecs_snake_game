#include "Components.h"
#include "Engine.h"
#include "InitSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "TextRenderSystem.h"

int main(int argc, char* argv[])
{
	constexpr size_t fieldSize = 20;
	constexpr size_t maxEntityCount = 30;
	constexpr size_t frameTime = 300;
	ecs_engine::Engine engine(maxEntityCount, frameTime);
	engine.RegisterComponents<
		game::Position,
		game::Symbol,
		game::Collidable,
		game::Direction,
		game::Field,
		game::Food,
		game::Growing,
		game::NextSegment,
		game::SnakeSegment,
		game::SnakeHead>();
	engine.AppendSystem<game::InitSystem>(fieldSize);
	engine.AppendSystem<game::InputSystem>();
	engine.AppendSystem<game::MovementSystem>();
	engine.AppendSystem<game::TextRenderSystem>(fieldSize);
	engine.Run();
}
