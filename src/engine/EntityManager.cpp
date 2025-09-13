#include "entity/EntityManager.h"

#include "component/ComponentManager.h"

namespace ecs_engine::entity
{

EntityManager::EntityManager(component::ComponentManager* componentManager, const size_t idPoolMax)
	: m_componentManager(componentManager)
	, m_idPool(std::move(std::make_unique<EntityIdPool>(idPoolMax)))
{
}

std::vector<EntityId> EntityManager::GetEntitiesBySignature(const core::Signature signature)
{
	std::vector<EntityId> result;
	result.reserve(m_entityIdToSignature.size());

	for (const auto& [entityId, entitySignature] : m_entityIdToSignature)
	{
		if ((entitySignature & signature) == signature)
		{
			result.push_back(entityId);
		}
	}

	return result;
}

std::vector<EntityId> EntityManager::GetAllEntities()
{
	std::vector<EntityId> result;
	result.reserve(m_entityIdToSignature.size());

	for (const auto& [entityId, entitySignature] : m_entityIdToSignature)
	{
		result.push_back(entityId);
	}

	return result;
}

void EntityManager::DeleteEntity(const EntityId entityId)
{
	const core::Signature signature = m_entityIdToSignature[entityId];
	m_entityIdToSignature.erase(entityId);
	for (size_t i = 0; i < MAX_COMPONENTS; ++i)
	{
		if (signature.test(i))
		{
			m_componentManager->DestroyComponent(entityId, i);
		}
	}
	m_idPool->ReleaseId(entityId);
}

} // namespace ecs_engine::entity
