#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "EntityIdPool.h"
#include "component/ComponentManager.h"
#include "core/SparseSet.h"

#include <unordered_map>

namespace ecs_engine::component
{
class ComponentManager;
}

namespace ecs_engine::entity
{

class EntityManager final
{

private:
	component::ComponentManager* m_componentManager;
	std::unique_ptr<EntityIdPool> m_idPool;
	std::unordered_map<core::Signature, core::SparseSet<EntityId>> m_signatureToEntityId;
	std::unordered_map<EntityId, core::Signature> m_entityIdToSignature;

	template <typename ComponentType> void CreateComponent(const EntityId entityId, core::Signature& entitySignature, ComponentType&& initialVal)
	{
		auto componentPoolId = m_componentManager->CreateComponent<ComponentType>(entityId, std::forward<ComponentType>(initialVal));
		entitySignature.set(componentPoolId);
	}

public:
	EntityManager(component::ComponentManager* componentManager, size_t idPoolMax);
	~EntityManager() = default;

	template <typename... ComponentTypes, typename... Args> EntityId CreateEntity(Args&&... args)
	{
		const auto entityId = m_idPool->AcquireId();
		core::Signature signature;
		(CreateComponent<ComponentTypes>(entityId, signature, std::forward<Args>(args)), ...);
		auto& set = m_signatureToEntityId[signature];
		set.Add(entityId);
		m_entityIdToSignature[entityId] = signature;
		return entityId;
	}

	std::vector<EntityId> GetEntitiesBySignature(core::Signature signature);
	void DeleteEntity(EntityId entityId);
};


}

#endif //ENTITYMANAGER_H
