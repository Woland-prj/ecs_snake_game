#ifndef ENGINE_H
#define ENGINE_H
#include "component/ComponentManager.h"
#include "core/EventBus.h"
#include "entity/EntityManager.h"
#include "system/SystemManager.h"

#include <chrono>

namespace ecs_engine
{

static constexpr int baseFrameTime = 33;

class Engine final
{
private:
	std::unique_ptr<core::EventBus> m_eventBus;
	std::unique_ptr<component::ComponentManager> m_componentManager;
	std::unique_ptr<entity::EntityManager> m_entityManager;
	std::unique_ptr<system::SystemManager> m_systemManager;
	std::chrono::steady_clock::time_point m_lastTick;
	const std::chrono::milliseconds m_frameTime{ 33 };

	static inline bool m_running = true;
	static void SignalHandler(int signum);

public:
	explicit Engine(size_t maxEntityCount, size_t frameTime);

	template <typename... ComponentTypes>
	void RegisterComponents()
	{
		(RegisterComponent<ComponentTypes>(), ...);
	}

	template <typename ComponentType>
	void RegisterComponent()
	{
		m_componentManager->RegisterComponent<ComponentType>();
	}

	template <typename SystemType, typename... Args>
	void AppendSystem(Args&&... args)
	{
		m_systemManager->RegisterSystem<SystemType>(std::forward<Args>(args)...);
	}

	void Run();
};
} // namespace ecs_engine

#endif // ENGINE_H
