#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "EntityIdPool.h"
#include "component/ComponentManager.h"
#include "core/Signature.h"

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
	std::unordered_map<EntityId, core::Signature> m_entityIdToSignature;

	template <typename ComponentType>
	void CreateComponentInternal(const EntityId entityId, core::Signature& entitySignature, ComponentType&& initialVal)
	{
		auto componentPoolId = m_componentManager->CreateComponent<ComponentType>(entityId, std::forward<ComponentType>(initialVal));
		entitySignature.set(componentPoolId);
	}

public:
	EntityManager(component::ComponentManager* componentManager, size_t idPoolMax);
	~EntityManager() = default;

	template <typename... ComponentTypes, typename... Args>
	EntityId CreateEntity(Args&&... args)
	{
		const auto entityId = m_idPool->AcquireId();
		core::Signature signature;
		(CreateComponentInternal<ComponentTypes>(entityId, signature, std::forward<Args>(args)), ...);
		m_entityIdToSignature[entityId] = signature;
		return entityId;
	}

	template <typename ComponentType>
	void AppendComponent(const EntityId entityId)
	{
		m_entityIdToSignature[entityId].set(m_componentManager->GetPoolId<ComponentType>());
	}

	template <typename ComponentType>
	bool HasComponent(EntityId entityId)
	{
		return m_entityIdToSignature[entityId].test(m_componentManager->GetPoolId<ComponentType>());
	}

	std::vector<EntityId> GetEntitiesBySignature(core::Signature signature);

	template <typename... ComponentTypes>
	std::vector<EntityId> GetEntitiesByComponents()
	{
		core::Signature signature;
		(signature.set(m_componentManager->GetPoolId<ComponentTypes>()), ...);
		return GetEntitiesBySignature(signature);
	};

	std::vector<EntityId> GetAllEntities();
	void DeleteEntity(EntityId entityId);
};

} // namespace ecs_engine::entity

#endif // ENTITYMANAGER_H
