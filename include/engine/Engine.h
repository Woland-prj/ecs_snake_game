#ifndef ENGINE_H
#define ENGINE_H
#include "component/ComponentManager.h"
#include "entity/EntityManager.h"
#include "system/SystemManager.h"

#include <iostream>

namespace ecs_engine
{
class Engine final
{
private:
	std::unique_ptr<component::ComponentManager> m_componentManager;
	std::unique_ptr<entity::EntityManager> m_entityManager;
	std::unique_ptr<system::SystemManager> m_systemManager;

	static inline bool m_running = true;
	static void SignalHandler(int signum);

public:
	explicit Engine(size_t maxEntityCount);

	template <typename... ComponentTypes> void RegisterComponents()
	{
		(RegisterComponent<ComponentTypes>(), ...);
	}

	template <typename ComponentType> void RegisterComponent()
	{
		m_componentManager->RegisterComponent<ComponentType>();
	}

	template <typename SystemType, typename... Args> void AppendSystem(Args&&... args)
	{
		m_systemManager->RegisterSystem<SystemType>(std::forward<Args>(args)...);
	}

	void Run() const;
};
}

#endif //ENGINE_H
