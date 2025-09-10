#include "Components.h"
#include "Engine.h"
#include "InputSystem.h"
#include "TextRenderSystem.h"
#define FIELD_SIZE 5
#define MAX_ENTITY 30

int main(int argc, char* argv[])
{
	ecs_engine::Engine engine(MAX_ENTITY, ecs_engine::baseFrameTime);
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
	engine.AppendSystem<game::InputSystem>();
	engine.AppendSystem<game::TextRenderSystem>(20);
	engine.Run();
}
