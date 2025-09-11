#include "component/ComponentManager.h"

namespace ecs_engine::component
{

ComponentManager::ComponentManager(const size_t maxPoolSize)
	: m_maxPoolSize(maxPoolSize)
{
}

void ComponentManager::DestroyComponent(const entity::EntityId entityId, const PoolId poolId) const
{
	m_poolRegistry[poolId]->Deallocate(entityId);
}

} // namespace ecs_engine::component
