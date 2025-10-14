#include "Engine.h"
#include <csignal>
#include <iostream>
#include <memory>
#include <thread>

namespace ecs_engine
{
void Engine::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "Catch interrupt signal. Stopping...\n";
	m_running = false;
}

Engine::Engine(size_t maxEntityCount, const size_t tickSpeed)
	: m_eventBus(std::make_unique<core::EventBus>())
	, m_componentManager(std::make_unique<component::ComponentManager>(maxEntityCount))
	, m_entityManager(std::make_unique<entity::EntityManager>(m_componentManager.get(), maxEntityCount))
	, m_systemManager(std::make_unique<system::SystemManager>(m_componentManager.get(), m_entityManager.get(), m_eventBus.get()))
	, m_tickSpeed(tickSpeed)
{
	std::signal(SIGINT, SignalHandler);
}

void Engine::Run() const
{
	m_systemManager->InitAll();
	const auto frameTime = std::chrono::milliseconds(S_TO_MS_CONV_CONST / m_tickSpeed);
	while (m_running)
	{

		const auto start = std::chrono::steady_clock::now();

		m_systemManager->TickAll();

		const auto stop = std::chrono::steady_clock::now();

		if (const auto workTime = stop - start; workTime < frameTime)
			std::this_thread::sleep_for(frameTime - workTime);
	}
}
} // namespace ecs_engine
