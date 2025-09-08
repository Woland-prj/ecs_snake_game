#ifndef SYSTEM_H
#define SYSTEM_H
#include "ISystem.h"
#include "component/ComponentManager.h"
#include "entity/EntityManager.h"

namespace ecs_engine::system
{
template <typename... ComponentTypes> class System : public ISystem
{
	friend class SystemManager;

private:
	core::Signature m_signature;

	template <typename ComponentType> void SetBitByComponentType()
	{
		auto id = m_componentManager->GetPoolId<ComponentType>();
		m_signature.set(id);
	}

	void InitSystem(component::ComponentManager* componentManager, entity::EntityManager* entityManager) override
	{
		m_componentManager = componentManager;
		m_entityManager = entityManager;
		(SetBitByComponentType<ComponentTypes>(), ...);
	}

protected:
	component::ComponentManager* m_componentManager = nullptr;
	entity::EntityManager* m_entityManager = nullptr;

	[[nodiscard]] entity::EntityManager* EntityManager() const
	{
		return m_entityManager;
	}

	[[nodiscard]] entity::EntityManager* ComponentManager() const
	{
		return m_entityManager;
	}

	auto Entities() const
	{
		return m_entityManager->GetEntitiesBySignature(m_signature);
	}
};
}

#endif //SYSTEM_H
