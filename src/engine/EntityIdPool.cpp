#include "entity/EntityIdPool.h"

namespace ecs_engine::entity
{
EntityIdPool::EntityIdPool(size_t initialSize)
{
	for (size_t i = 0; i < initialSize; i++)
	{
		m_freeIndexes.push(i);
	}
}

EntityId EntityIdPool::AcquireId()
{
	const auto id = m_freeIndexes.front();
	m_freeIndexes.pop();
	return id;
}

void EntityIdPool::ReleaseId(const EntityId entityId)
{
	m_freeIndexes.push(entityId);
}

}