#include "entity/EntityManager.h"

#include "component/ComponentManager.h"

namespace ecs_engine::entity
{

EntityManager::EntityManager(component::ComponentManager* componentManager, const size_t idPoolMax)
	: m_componentManager(componentManager), m_idPool(std::move(std::make_unique<EntityIdPool>(idPoolMax)))
{
}

std::vector<EntityId> EntityManager::GetEntitiesBySignature(const core::Signature signature)
{
	const auto it = m_signatureToEntityId.find(signature);
	if (it == m_signatureToEntityId.end())
	{
		return {};
	}
	const auto& ss = it->second;
	std::vector<EntityId> result(ss.Size());
	std::copy_n(ss.Data(), ss.Size(), result.begin());
	return result;
}

void EntityManager::DeleteEntity(const EntityId entityId)
{
	core::Signature signature = m_entityIdToSignature[entityId];
	m_signatureToEntityId.erase(signature);
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

}