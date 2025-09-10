#ifndef ICOMPONENTPOOL_H
#define ICOMPONENTPOOL_H
#include "entity/EntityIdPool.h"

namespace ecs_engine::component
{
class IComponentPool
{
public:
	virtual void Deallocate(entity::EntityId entityId) = 0;
	virtual ~IComponentPool() = default;
};
} // namespace ecs_engine::component

#endif // ICOMPONENTPOOL_H
