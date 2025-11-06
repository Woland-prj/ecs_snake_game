#include "CollisionSystem.h"
#include "Components.h"
#include "Engine.h"
#include "FoodSpawnSystem.h"
#include "GraphicsInputSystem.h"
#include "GraphicsRenderSystem.h"
#include "GrowingSystem.h"
#include "InitSystem.h"
#include "MovementSystem.h"

int main(int argc, char* argv[])
{
	constexpr size_t fieldSize = 20;
	constexpr size_t maxEntityCount = 10000;
	constexpr size_t tickSpeed = 5;
	ecs_engine::Engine engine(maxEntityCount, tickSpeed);
	engine.RegisterComponents<
		game::Position,
		game::Symbol,
		game::Direction,
		game::Field,
		game::Food,
		game::Growing,
		game::NextSegment,
		game::SnakeSegment,
		game::SnakeHead,
		game::Color
	>();
	engine.AppendSystem<game::InitSystem>(fieldSize);
	engine.AppendSystem<game::FoodSpawnSystem>(fieldSize);
	engine.AppendSystem<game::GraphicsInputSystem>();
	engine.AppendSystem<game::MovementSystem>();
	engine.AppendSystem<game::CollisionSystem>(fieldSize);
	engine.AppendSystem<game::GrowingSystem>(fieldSize);
	engine.AppendSystem<game::GraphicsRenderSystem>(fieldSize);
	engine.Run();
}
