#include "Engine.h"
#include <csignal>

namespace ecs_engine
{
void Engine::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "Catch interrupt signal. Stopping...\n";
	m_running = false;
}

Engine::Engine(size_t maxEntityCount, const size_t frameTime)
	: m_componentManager(std::make_unique<component::ComponentManager>(maxEntityCount))
	  , m_entityManager(std::make_unique<entity::EntityManager>(m_componentManager.get(), maxEntityCount))
	  , m_systemManager(std::make_unique<system::SystemManager>(m_componentManager.get(), m_entityManager.get()))
	  , m_frameTime(frameTime)
{
	std::signal(SIGINT, SignalHandler);
}

void Engine::Run()
{
	m_systemManager->InitAll();
	while (m_running)
	{
		const auto now = std::chrono::steady_clock::now();

		if (const auto delta = now - m_lastTick; delta < m_frameTime)
			continue;

		m_lastTick = now;

		m_systemManager->TickAll();
	}
}
}