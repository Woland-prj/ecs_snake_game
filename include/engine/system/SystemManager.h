#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include "ISystem.h"
#include "component/ComponentManager.h"
#include "entity/EntityManager.h"

#include <vector>

namespace ecs_engine::system
{

class SystemManager
{
private:
	component::ComponentManager* m_componentManager;
	entity::EntityManager* m_entityManager;
	std::vector<std::unique_ptr<ISystem>> m_systems;

public:
	SystemManager(component::ComponentManager* componentManager, entity::EntityManager* entityManager);
	~SystemManager() = default;

	template <typename S, typename... Args>
	void RegisterSystem(Args&&... args)
	{
		static_assert(std::is_base_of_v<ISystem, S>, "S must be derived from ISystem");
		std::unique_ptr<ISystem> system = std::make_unique<S>(std::forward<Args>(args)...);
		system->InitSystem(m_componentManager, m_entityManager);
		m_systems.push_back(std::move(system));
	}

	void InitAll() const;
	void TickAll() const;
};
} // namespace ecs_engine::system

#endif // SYSTEMMANAGER_H