#ifndef ENTITYIDPOOL_H
#define ENTITYIDPOOL_H
#include <queue>

namespace ecs_engine::entity
{
using EntityId = size_t;

class EntityIdPool
{
private:
	std::queue<size_t> m_freeIndexes;

public:
	EntityIdPool() = delete;
	explicit EntityIdPool(size_t initialSize);
	EntityId AcquireId();
	void ReleaseId(EntityId entityId);
};
} // namespace ecs_engine::entity

#endif // ENTITYIDPOOL_H
