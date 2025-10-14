#ifndef ENGINE_H
#define ENGINE_H
#include "component/ComponentManager.h"
#include "core/EventBus.h"
#include "entity/EntityManager.h"
#include "system/SystemManager.h"
#define S_TO_MS_CONV_CONST 1000

namespace ecs_engine
{

static constexpr int baseFrameTime = 33;

class Engine final
{
public:
	explicit Engine(size_t maxEntityCount, size_t tickSpeed);

	template <typename... ComponentTypes>
	void RegisterComponents() const
	{
		(RegisterComponent<ComponentTypes>(), ...);
	}

	template <typename ComponentType>
	void RegisterComponent() const
	{
		m_componentManager->RegisterComponent<ComponentType>();
	}

	template <typename SystemType, typename... Args>
	void AppendSystem(Args&&... args)
	{
		m_systemManager->RegisterSystem<SystemType>(std::forward<Args>(args)...);
	}

	void Run() const;

private:
	std::unique_ptr<core::EventBus> m_eventBus;
	std::unique_ptr<component::ComponentManager> m_componentManager;
	std::unique_ptr<entity::EntityManager> m_entityManager;
	std::unique_ptr<system::SystemManager> m_systemManager;
	uint8_t m_tickSpeed;

	static inline bool m_running = true;
	static void SignalHandler(int signum);
};
} // namespace ecs_engine

#endif // ENGINE_H
