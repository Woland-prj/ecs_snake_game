#ifndef SYSTEM_H
#define SYSTEM_H
#include "ISystem.h"
#include "component/ComponentManager.h"
#include "core/EventBus.h"
#include "entity/EntityManager.h"

namespace ecs_engine::system
{
template <typename... ComponentTypes>
class System : public ISystem
{
	friend class SystemManager;

private:
	core::Signature m_signature;

	template <typename ComponentType>
	void SetBitByComponentType()
	{
		auto id = m_componentManager->GetPoolId<ComponentType>();
		m_signature.set(id);
	}

	void InitSystem(component::ComponentManager* componentManager, entity::EntityManager* entityManager, core::EventBus* eventBus) override
	{
		m_componentManager = componentManager;
		m_entityManager = entityManager;
		m_eventBus = eventBus;
		(SetBitByComponentType<ComponentTypes>(), ...);
	}

protected:
	component::ComponentManager* m_componentManager = nullptr;
	entity::EntityManager* m_entityManager = nullptr;
	core::EventBus* m_eventBus = nullptr;

	[[nodiscard]] entity::EntityManager* EntityManager() const
	{
		return m_entityManager;
	}

	[[nodiscard]] component::ComponentManager* ComponentManager() const
	{
		return m_componentManager;
	}

	[[nodiscard]] core::EventBus* EventBus() const
	{
		return m_eventBus;
	}

	auto Entities() const
	{
		return m_entityManager->GetEntitiesBySignature(m_signature);
	}
};
} // namespace ecs_engine::system

#endif // SYSTEM_H
